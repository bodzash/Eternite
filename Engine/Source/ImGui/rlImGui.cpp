/**********************************************************************************************
*
*   raylibExtras * Utilities and Shared Components for Raylib
*
*   rlImGui * basic ImGui integration
*
*   LICENSE: ZLIB
*
*   Copyright (c) 2020 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/
#include "rlImGui.h"
#include "imgui_impl_raylib.h"

namespace Raylib {
    #include "raylib.h"
    #include "rlgl.h"
}

/*
#ifdef PLATFORM_DESKTOP
#include <GLFW/glfw3.h>
#endif
*/

#include <math.h>
#include <map>

/*
#ifndef NO_FONT_AWESOME
#include "extras/FA6FreeSolidFontData.h"
#endif
*/
using KeyboardKey = int;
using MouseCursor = int;

static ImGuiMouseCursor CurrentMouseCursor = ImGuiMouseCursor_COUNT;
static MouseCursor MouseCursorMap[ImGuiMouseCursor_COUNT];

ImGuiContext* GlobalContext = nullptr;


static std::map<KeyboardKey, ImGuiKey> RaylibKeyMap;

static bool LastFrameFocused = false;

static bool LastControlPressed = false;
static bool LastShiftPressed = false;
static bool LastAltPressed = false;
static bool LastSuperPressed = false;

bool rlImGuiIsControlDown() { return Raylib::IsKeyDown(Raylib::KEY_RIGHT_CONTROL) || Raylib::IsKeyDown(Raylib::KEY_LEFT_CONTROL); }
bool rlImGuiIsShiftDown() { return Raylib::IsKeyDown(Raylib::KEY_RIGHT_SHIFT) || Raylib::IsKeyDown(Raylib::KEY_LEFT_SHIFT); }
bool rlImGuiIsAltDown() { return Raylib::IsKeyDown(Raylib::KEY_RIGHT_ALT) || Raylib::IsKeyDown(Raylib::KEY_LEFT_ALT); }
bool rlImGuiIsSuperDown() { return Raylib::IsKeyDown(Raylib::KEY_RIGHT_SUPER) || Raylib::IsKeyDown(Raylib::KEY_LEFT_SUPER); }

void ReloadFonts()
{
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels = nullptr;

	int width;
	int height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, nullptr);
	Raylib::Image image = Raylib::GenImageColor(width, height, Raylib::BLANK);
	memcpy(image.data, pixels, width * height * 4);

	Raylib::Texture2D* fontTexture = (Raylib::Texture2D*)io.Fonts->TexID;
	if (fontTexture && fontTexture->id != 0)
	{
		Raylib::UnloadTexture(*fontTexture);
		MemFree(fontTexture);
	}

	fontTexture = (Raylib::Texture2D*)Raylib::MemAlloc(sizeof(Raylib::Texture2D));
	*fontTexture = Raylib::LoadTextureFromImage(image);
	Raylib::UnloadImage(image);
	io.Fonts->TexID = fontTexture;
}

static const char* GetClipTextCallback(void*) 
{
    return Raylib::GetClipboardText();
}

static void SetClipTextCallback(void*, const char* text)
{
    Raylib::SetClipboardText(text);
}

static void ImGuiNewFrame(float deltaTime)
{
    ImGuiIO& io = ImGui::GetIO();

    if (Raylib::IsWindowFullscreen())
    {
        int monitor = Raylib::GetCurrentMonitor();
        io.DisplaySize.x = float(Raylib::GetMonitorWidth(monitor));
        io.DisplaySize.y = float(Raylib::GetMonitorHeight(monitor));
    }
    else
    {
        io.DisplaySize.x = float(Raylib::GetScreenWidth());
        io.DisplaySize.y = float(Raylib::GetScreenHeight());
    }

    int width = int(io.DisplaySize.x), height = int(io.DisplaySize.y);
/*
#ifdef PLATFORM_DESKTOP
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
#endif
*/
    if (width > 0 && height > 0) 
    {
        io.DisplayFramebufferScale = ImVec2(width / io.DisplaySize.x, height / io.DisplaySize.y);
    }
    else 
    {
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    }

    io.DeltaTime = deltaTime;

    if (io.WantSetMousePos)
    {
        Raylib::SetMousePosition((int)io.MousePos.x, (int)io.MousePos.y);
    }
    else
    {
        io.MousePos.x = (float)Raylib::GetMouseX();
        io.MousePos.y = (float)Raylib::GetMouseY();
    }

    io.MouseDown[0] = Raylib::IsMouseButtonDown(Raylib::MOUSE_LEFT_BUTTON);
    io.MouseDown[1] = Raylib::IsMouseButtonDown(Raylib::MOUSE_RIGHT_BUTTON);
    io.MouseDown[2] = Raylib::IsMouseButtonDown(Raylib::MOUSE_MIDDLE_BUTTON);

    {
        Raylib::Vector2 mouseWheel = Raylib::GetMouseWheelMoveV();
        io.MouseWheel += mouseWheel.y;
        io.MouseWheelH += mouseWheel.x;
    }

    if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) == 0)
    {
        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        if (imgui_cursor != CurrentMouseCursor || io.MouseDrawCursor)
        {
            CurrentMouseCursor = imgui_cursor;
            if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
            {
                Raylib::HideCursor();
            }
            else
            {
                Raylib::ShowCursor();

                if (!(io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange))
                {
                    Raylib::SetMouseCursor((imgui_cursor > -1 && imgui_cursor < ImGuiMouseCursor_COUNT) ? MouseCursorMap[imgui_cursor] : Raylib::MOUSE_CURSOR_DEFAULT);
                }
            }
        }
    }
}

static void ImGuiTriangleVert(ImDrawVert& idx_vert)
{
    Raylib::Color* c;
    c = (Raylib::Color*)&idx_vert.col;
    Raylib::rlColor4ub(c->r, c->g, c->b, c->a);
    Raylib::rlTexCoord2f(idx_vert.uv.x, idx_vert.uv.y);
    Raylib::rlVertex2f(idx_vert.pos.x, idx_vert.pos.y);
}

static void ImGuiRenderTriangles(unsigned int count, int indexStart, const ImVector<ImDrawIdx>& indexBuffer, const ImVector<ImDrawVert>& vertBuffer, void* texturePtr)
{
    if (count < 3)
        return;

    Raylib::Texture* texture = (Raylib::Texture*)texturePtr;

    unsigned int textureId = (texture == nullptr) ? 0 : texture->id;

    Raylib::rlBegin(RL_TRIANGLES);
    Raylib::rlSetTexture(textureId);

    for (unsigned int i = 0; i <= (count - 3); i += 3)
    {
        if (Raylib::rlCheckRenderBatchLimit(3))
        {
            Raylib::rlBegin(RL_TRIANGLES);
            Raylib::rlSetTexture(textureId);
        }

        ImDrawIdx indexA = indexBuffer[indexStart + i];
        ImDrawIdx indexB = indexBuffer[indexStart + i + 1];
        ImDrawIdx indexC = indexBuffer[indexStart + i + 2];

        ImDrawVert vertexA = vertBuffer[indexA];
        ImDrawVert vertexB = vertBuffer[indexB];
        ImDrawVert vertexC = vertBuffer[indexC];

        ImGuiTriangleVert(vertexA);
        ImGuiTriangleVert(vertexB);
        ImGuiTriangleVert(vertexC);
    }
    Raylib::rlEnd();
}

static void EnableScissor(float x, float y, float width, float height)
{
    Raylib::rlEnableScissorTest();
    ImGuiIO& io = ImGui::GetIO();
    Raylib::rlScissor((int)(x * io.DisplayFramebufferScale.x),
        int((Raylib::GetScreenHeight() - (int)(y + height)) * io.DisplayFramebufferScale.y),
        (int)(width * io.DisplayFramebufferScale.x),
        (int)(height * io.DisplayFramebufferScale.y));
}

static void SetupMouseCursors()
{
    MouseCursorMap[ImGuiMouseCursor_Arrow] = Raylib::MOUSE_CURSOR_ARROW;
    MouseCursorMap[ImGuiMouseCursor_TextInput] = Raylib::MOUSE_CURSOR_IBEAM;
    MouseCursorMap[ImGuiMouseCursor_Hand] = Raylib::MOUSE_CURSOR_POINTING_HAND;
    MouseCursorMap[ImGuiMouseCursor_ResizeAll] = Raylib::MOUSE_CURSOR_RESIZE_ALL;
    MouseCursorMap[ImGuiMouseCursor_ResizeEW] = Raylib::MOUSE_CURSOR_RESIZE_EW;
    MouseCursorMap[ImGuiMouseCursor_ResizeNESW] = Raylib::MOUSE_CURSOR_RESIZE_NESW;
    MouseCursorMap[ImGuiMouseCursor_ResizeNS] = Raylib::MOUSE_CURSOR_RESIZE_NS;
    MouseCursorMap[ImGuiMouseCursor_ResizeNWSE] = Raylib::MOUSE_CURSOR_RESIZE_NWSE;
    MouseCursorMap[ImGuiMouseCursor_NotAllowed] = Raylib::MOUSE_CURSOR_NOT_ALLOWED;
}

void SetupFontAwesome()
{
    /*
#ifndef NO_FONT_AWESOME
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.FontDataOwnedByAtlas = false;

	icons_config.GlyphRanges = icons_ranges;

    ImGuiIO& io = ImGui::GetIO();

	io.Fonts->AddFontFromMemoryCompressedTTF((void*)fa_solid_900_compressed_data, fa_solid_900_compressed_size, FONT_AWESOME_ICON_SIZE, &icons_config, icons_ranges);
#endif
*/
}

void SetupBackend()
{
    ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = "imgui_impl_raylib";

	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

	io.MousePos = ImVec2(0, 0);

	io.SetClipboardTextFn = SetClipTextCallback;
	io.GetClipboardTextFn = GetClipTextCallback;

	io.ClipboardUserData = nullptr;
}

void rlImGuiEndInitImGui()
{
    ImGui::SetCurrentContext(GlobalContext);

    SetupFontAwesome();

    SetupMouseCursors();

    SetupBackend();

    ReloadFonts();
}

static void SetupKeymap()
{
    if (!RaylibKeyMap.empty())
        return;

    // build up a map of raylib keys to ImGuiKeys
    RaylibKeyMap[Raylib::KEY_APOSTROPHE] = ImGuiKey_Apostrophe;
    RaylibKeyMap[Raylib::KEY_COMMA] = ImGuiKey_Comma;
    RaylibKeyMap[Raylib::KEY_MINUS] = ImGuiKey_Minus;
    RaylibKeyMap[Raylib::KEY_PERIOD] = ImGuiKey_Period;
    RaylibKeyMap[Raylib::KEY_SLASH] = ImGuiKey_Slash;
    RaylibKeyMap[Raylib::KEY_ZERO] = ImGuiKey_0;
    RaylibKeyMap[Raylib::KEY_ONE] = ImGuiKey_1;
    RaylibKeyMap[Raylib::KEY_TWO] = ImGuiKey_2;
    RaylibKeyMap[Raylib::KEY_THREE] = ImGuiKey_3;
    RaylibKeyMap[Raylib::KEY_FOUR] = ImGuiKey_4;
    RaylibKeyMap[Raylib::KEY_FIVE] = ImGuiKey_5;
    RaylibKeyMap[Raylib::KEY_SIX] = ImGuiKey_6;
    RaylibKeyMap[Raylib::KEY_SEVEN] = ImGuiKey_7;
    RaylibKeyMap[Raylib::KEY_EIGHT] = ImGuiKey_8;
    RaylibKeyMap[Raylib::KEY_NINE] = ImGuiKey_9;
    RaylibKeyMap[Raylib::KEY_SEMICOLON] = ImGuiKey_Semicolon;
    RaylibKeyMap[Raylib::KEY_EQUAL] = ImGuiKey_Equal;
    RaylibKeyMap[Raylib::KEY_A] = ImGuiKey_A;
    RaylibKeyMap[Raylib::KEY_B] = ImGuiKey_B;
    RaylibKeyMap[Raylib::KEY_C] = ImGuiKey_C;
    RaylibKeyMap[Raylib::KEY_D] = ImGuiKey_D;
    RaylibKeyMap[Raylib::KEY_E] = ImGuiKey_E;
    RaylibKeyMap[Raylib::KEY_F] = ImGuiKey_F;
    RaylibKeyMap[Raylib::KEY_G] = ImGuiKey_G;
    RaylibKeyMap[Raylib::KEY_H] = ImGuiKey_H;
    RaylibKeyMap[Raylib::KEY_I] = ImGuiKey_I;
    RaylibKeyMap[Raylib::KEY_J] = ImGuiKey_J;
    RaylibKeyMap[Raylib::KEY_K] = ImGuiKey_K;
    RaylibKeyMap[Raylib::KEY_L] = ImGuiKey_L;
    RaylibKeyMap[Raylib::KEY_M] = ImGuiKey_M;
    RaylibKeyMap[Raylib::KEY_N] = ImGuiKey_N;
    RaylibKeyMap[Raylib::KEY_O] = ImGuiKey_O;
    RaylibKeyMap[Raylib::KEY_P] = ImGuiKey_P;
    RaylibKeyMap[Raylib::KEY_Q] = ImGuiKey_Q;
    RaylibKeyMap[Raylib::KEY_R] = ImGuiKey_R;
    RaylibKeyMap[Raylib::KEY_S] = ImGuiKey_S;
    RaylibKeyMap[Raylib::KEY_T] = ImGuiKey_T;
    RaylibKeyMap[Raylib::KEY_U] = ImGuiKey_U;
    RaylibKeyMap[Raylib::KEY_V] = ImGuiKey_V;
    RaylibKeyMap[Raylib::KEY_W] = ImGuiKey_W;
    RaylibKeyMap[Raylib::KEY_X] = ImGuiKey_X;
    RaylibKeyMap[Raylib::KEY_Y] = ImGuiKey_Y;
    RaylibKeyMap[Raylib::KEY_Z] = ImGuiKey_Z;
    RaylibKeyMap[Raylib::KEY_SPACE] = ImGuiKey_Space;
    RaylibKeyMap[Raylib::KEY_ESCAPE] = ImGuiKey_Escape;
    RaylibKeyMap[Raylib::KEY_ENTER] = ImGuiKey_Enter;
    RaylibKeyMap[Raylib::KEY_TAB] = ImGuiKey_Tab;
    RaylibKeyMap[Raylib::KEY_BACKSPACE] = ImGuiKey_Backspace;
    RaylibKeyMap[Raylib::KEY_INSERT] = ImGuiKey_Insert;
    RaylibKeyMap[Raylib::KEY_DELETE] = ImGuiKey_Delete;
    RaylibKeyMap[Raylib::KEY_RIGHT] = ImGuiKey_RightArrow;
    RaylibKeyMap[Raylib::KEY_LEFT] = ImGuiKey_LeftArrow;
    RaylibKeyMap[Raylib::KEY_DOWN] = ImGuiKey_DownArrow;
    RaylibKeyMap[Raylib::KEY_UP] = ImGuiKey_UpArrow;
    RaylibKeyMap[Raylib::KEY_PAGE_UP] = ImGuiKey_PageUp;
    RaylibKeyMap[Raylib::KEY_PAGE_DOWN] = ImGuiKey_PageDown;
    RaylibKeyMap[Raylib::KEY_HOME] = ImGuiKey_Home;
    RaylibKeyMap[Raylib::KEY_END] = ImGuiKey_End;
    RaylibKeyMap[Raylib::KEY_CAPS_LOCK] = ImGuiKey_CapsLock;
    RaylibKeyMap[Raylib::KEY_SCROLL_LOCK] = ImGuiKey_ScrollLock;
    RaylibKeyMap[Raylib::KEY_NUM_LOCK] = ImGuiKey_NumLock;
    RaylibKeyMap[Raylib::KEY_PRINT_SCREEN] = ImGuiKey_PrintScreen;
    RaylibKeyMap[Raylib::KEY_PAUSE] = ImGuiKey_Pause;
    RaylibKeyMap[Raylib::KEY_F1] = ImGuiKey_F1;
    RaylibKeyMap[Raylib::KEY_F2] = ImGuiKey_F2;
    RaylibKeyMap[Raylib::KEY_F3] = ImGuiKey_F3;
    RaylibKeyMap[Raylib::KEY_F4] = ImGuiKey_F4;
    RaylibKeyMap[Raylib::KEY_F5] = ImGuiKey_F5;
    RaylibKeyMap[Raylib::KEY_F6] = ImGuiKey_F6;
    RaylibKeyMap[Raylib::KEY_F7] = ImGuiKey_F7;
    RaylibKeyMap[Raylib::KEY_F8] = ImGuiKey_F8;
    RaylibKeyMap[Raylib::KEY_F9] = ImGuiKey_F9;
    RaylibKeyMap[Raylib::KEY_F10] = ImGuiKey_F10;
    RaylibKeyMap[Raylib::KEY_F11] = ImGuiKey_F11;
    RaylibKeyMap[Raylib::KEY_F12] = ImGuiKey_F12;
    RaylibKeyMap[Raylib::KEY_LEFT_SHIFT] = ImGuiKey_LeftShift;
    RaylibKeyMap[Raylib::KEY_LEFT_CONTROL] = ImGuiKey_LeftCtrl;
    RaylibKeyMap[Raylib::KEY_LEFT_ALT] = ImGuiKey_LeftAlt;
    RaylibKeyMap[Raylib::KEY_LEFT_SUPER] = ImGuiKey_LeftSuper;
    RaylibKeyMap[Raylib::KEY_RIGHT_SHIFT] = ImGuiKey_RightShift;
    RaylibKeyMap[Raylib::KEY_RIGHT_CONTROL] = ImGuiKey_RightCtrl;
    RaylibKeyMap[Raylib::KEY_RIGHT_ALT] = ImGuiKey_RightAlt;
    RaylibKeyMap[Raylib::KEY_RIGHT_SUPER] = ImGuiKey_RightSuper;
    RaylibKeyMap[Raylib::KEY_KB_MENU] = ImGuiKey_Menu;
    RaylibKeyMap[Raylib::KEY_LEFT_BRACKET] = ImGuiKey_LeftBracket;
    RaylibKeyMap[Raylib::KEY_BACKSLASH] = ImGuiKey_Backslash;
    RaylibKeyMap[Raylib::KEY_RIGHT_BRACKET] = ImGuiKey_RightBracket;
    RaylibKeyMap[Raylib::KEY_GRAVE] = ImGuiKey_GraveAccent;
    RaylibKeyMap[Raylib::KEY_KP_0] = ImGuiKey_Keypad0;
    RaylibKeyMap[Raylib::KEY_KP_1] = ImGuiKey_Keypad1;
    RaylibKeyMap[Raylib::KEY_KP_2] = ImGuiKey_Keypad2;
    RaylibKeyMap[Raylib::KEY_KP_3] = ImGuiKey_Keypad3;
    RaylibKeyMap[Raylib::KEY_KP_4] = ImGuiKey_Keypad4;
    RaylibKeyMap[Raylib::KEY_KP_5] = ImGuiKey_Keypad5;
    RaylibKeyMap[Raylib::KEY_KP_6] = ImGuiKey_Keypad6;
    RaylibKeyMap[Raylib::KEY_KP_7] = ImGuiKey_Keypad7;
    RaylibKeyMap[Raylib::KEY_KP_8] = ImGuiKey_Keypad8;
    RaylibKeyMap[Raylib::KEY_KP_9] = ImGuiKey_Keypad9;
    RaylibKeyMap[Raylib::KEY_KP_DECIMAL] = ImGuiKey_KeypadDecimal;
    RaylibKeyMap[Raylib::KEY_KP_DIVIDE] = ImGuiKey_KeypadDivide;
    RaylibKeyMap[Raylib::KEY_KP_MULTIPLY] = ImGuiKey_KeypadMultiply;
    RaylibKeyMap[Raylib::KEY_KP_SUBTRACT] = ImGuiKey_KeypadSubtract;
    RaylibKeyMap[Raylib::KEY_KP_ADD] = ImGuiKey_KeypadAdd;
    RaylibKeyMap[Raylib::KEY_KP_ENTER] = ImGuiKey_KeypadEnter;
    RaylibKeyMap[Raylib::KEY_KP_EQUAL] = ImGuiKey_KeypadEqual;
}

static void SetupGlobals()
{
	LastFrameFocused = Raylib::IsWindowFocused();
	LastControlPressed = false;
	LastShiftPressed = false;
	LastAltPressed = false;
	LastSuperPressed = false;

}

void rlImGuiBeginInitImGui()
{
    SetupGlobals();
    GlobalContext = ImGui::CreateContext(nullptr);
    SetupKeymap();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
}

void rlImGuiSetup(bool dark)
{
    rlImGuiBeginInitImGui();

    if (dark)
        ImGui::StyleColorsDark();
    else
        ImGui::StyleColorsLight();

    rlImGuiEndInitImGui();
}

void rlImGuiReloadFonts()
{
    ImGui::SetCurrentContext(GlobalContext);

    ReloadFonts();
}

void rlImGuiBegin()
{
    ImGui::SetCurrentContext(GlobalContext);
    rlImGuiBeginDelta(Raylib::GetFrameTime());
}

void rlImGuiBeginDelta(float deltaTime)
{
    ImGui::SetCurrentContext(GlobalContext);
	ImGuiNewFrame(deltaTime);
    ImGui_ImplRaylib_ProcessEvents();
	ImGui::NewFrame();
}

void rlImGuiEnd()
{
    ImGui::SetCurrentContext(GlobalContext);
    ImGui::Render();
    ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
}

void rlImGuiShutdown()
{
	ImGui::SetCurrentContext(GlobalContext);
    ImGui_ImplRaylib_Shutdown();

    ImGui::DestroyContext();
}

void rlImGuiImage(const Raylib::Texture* image)
{
	if (!image)
		return;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
    ImGui::Image((ImTextureID)image, ImVec2(float(image->width), float(image->height)));
}

bool rlImGuiImageButton(const char* name, const Raylib::Texture* image)
{
	if (!image)
		return false;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
    return ImGui::ImageButton(name, (ImTextureID)image, ImVec2(float(image->width), float(image->height)));
}

bool rlImGuiImageButtonSize(const char* name, const Raylib::Texture* image, ImVec2 size)
{
	if (!image)
		return false;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
    return ImGui::ImageButton(name, (ImTextureID)image, size);
}

void rlImGuiImageSize(const Raylib::Texture* image, int width, int height)
{
	if (!image)
		return;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
    ImGui::Image((ImTextureID)image, ImVec2(float(width), float(height)));
}

void rlImGuiImageSizeV(const Raylib::Texture* image, Raylib::Vector2 size)
{
	if (!image)
		return;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
	ImGui::Image((ImTextureID)image, ImVec2(size.x, size.y));
}

void rlImGuiImageRect(const Raylib::Texture* image, int destWidth, int destHeight, Raylib::Rectangle sourceRect)
{
	if (!image)
		return;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);
    ImVec2 uv0;
    ImVec2 uv1;

    if (sourceRect.width < 0)
    {
        uv0.x = -((float)sourceRect.x / image->width);
        uv1.x = (uv0.x - (float)(fabs(sourceRect.width) / image->width));
    }
    else
    {
        uv0.x = (float)sourceRect.x / image->width;
        uv1.x = uv0.x + (float)(sourceRect.width / image->width);
    }

    if (sourceRect.height < 0)
    {
        uv0.y = -((float)sourceRect.y / image->height);
        uv1.y = (uv0.y - (float)(fabs(sourceRect.height) / image->height));
    }
    else
    {
        uv0.y = (float)sourceRect.y / image->height;
        uv1.y = uv0.y + (float)(sourceRect.height / image->height);
    }

    ImGui::Image((ImTextureID)image, ImVec2(float(destWidth), float(destHeight)), uv0, uv1);
}

void rlImGuiImageRenderTexture(const Raylib::RenderTexture* image)
{
    if (!image)
        return;
    if (GlobalContext)
        ImGui::SetCurrentContext(GlobalContext);
    rlImGuiImageRect(&image->texture, image->texture.width, image->texture.height, Raylib::Rectangle{ 0,0, float(image->texture.width), -float(image->texture.height) });
}

void rlImGuiImageRenderTextureFit(const Raylib::RenderTexture* image, bool center)
{
	if (!image)
		return;
	if (GlobalContext)
		ImGui::SetCurrentContext(GlobalContext);

    ImVec2 area = ImGui::GetContentRegionAvail();

    float scale =  area.x / image->texture.width;

    float y = image->texture.height * scale;
    if (y > area.y)
    {
        scale = area.y / image->texture.height;
    }

    int sizeX = int(image->texture.width * scale);
    int sizeY = int(image->texture.height * scale);

    if (center)
    {
        ImGui::SetCursorPosX(0);
        ImGui::SetCursorPosX(area.x/2 - sizeX/2);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (area.y / 2 - sizeY / 2));
    }

    rlImGuiImageRect(&image->texture, sizeX, sizeY, Raylib::Rectangle{ 0,0, float(image->texture.width), -float(image->texture.height) });
}

// raw ImGui backend API
bool ImGui_ImplRaylib_Init()
{
    SetupGlobals();

	SetupKeymap();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

    SetupFontAwesome();

	SetupMouseCursors();

    SetupBackend();

    ReloadFonts();

    return true;
}

void ImGui_ImplRaylib_Shutdown()
{
    ImGuiIO& io =ImGui::GetIO();
    Raylib::Texture2D* fontTexture = (Raylib::Texture2D*)io.Fonts->TexID;

    if (fontTexture && fontTexture->id != 0)
	Raylib::UnloadTexture(*fontTexture);

    io.Fonts->TexID = 0;
}

void ImGui_ImplRaylib_NewFrame()
{
    ImGuiNewFrame(Raylib::GetFrameTime());
}

void ImGui_ImplRaylib_RenderDrawData(ImDrawData* draw_data)
{
	Raylib::rlDrawRenderBatchActive();
	Raylib::rlDisableBackfaceCulling();

	for (int l = 0; l < draw_data->CmdListsCount; ++l)
	{
		const ImDrawList* commandList = draw_data->CmdLists[l];

		for (const auto& cmd : commandList->CmdBuffer)
		{
			EnableScissor(cmd.ClipRect.x - draw_data->DisplayPos.x, cmd.ClipRect.y - draw_data->DisplayPos.y, cmd.ClipRect.z - (cmd.ClipRect.x - draw_data->DisplayPos.x), cmd.ClipRect.w - (cmd.ClipRect.y - draw_data->DisplayPos.y));
			if (cmd.UserCallback != nullptr)
			{
				cmd.UserCallback(commandList, &cmd);

				continue;
			}

			ImGuiRenderTriangles(cmd.ElemCount, cmd.IdxOffset, commandList->IdxBuffer, commandList->VtxBuffer, cmd.TextureId);
			Raylib::rlDrawRenderBatchActive();
		}
	}

	Raylib::rlSetTexture(0);
	Raylib::rlDisableScissorTest();
	Raylib::rlEnableBackfaceCulling();
}

bool ImGui_ImplRaylib_ProcessEvents()
{
	ImGuiIO& io = ImGui::GetIO();

	bool focused = Raylib::IsWindowFocused();
	if (focused != LastFrameFocused)
		io.AddFocusEvent(focused);
	LastFrameFocused = focused;

	// handle the modifyer key events so that shortcuts work
	bool ctrlDown = rlImGuiIsControlDown();
	if (ctrlDown != LastControlPressed)
		io.AddKeyEvent(ImGuiMod_Ctrl, ctrlDown);
	LastControlPressed = ctrlDown;

	bool shiftDown = rlImGuiIsShiftDown();
	if (shiftDown != LastShiftPressed)
		io.AddKeyEvent(ImGuiMod_Shift, shiftDown);
	LastShiftPressed = shiftDown;

	bool altDown = rlImGuiIsAltDown();
	if (altDown != LastAltPressed)
		io.AddKeyEvent(ImGuiMod_Alt, altDown);
	LastAltPressed = altDown;

	bool superDown = rlImGuiIsSuperDown();
	if (superDown != LastSuperPressed)
		io.AddKeyEvent(ImGuiMod_Super, superDown);
	LastSuperPressed = superDown;

	// get the pressed keys, they are in event order
	int keyId = Raylib::GetKeyPressed();
	while (keyId != 0)
	{
		auto keyItr = RaylibKeyMap.find(KeyboardKey(keyId));
		if (keyItr != RaylibKeyMap.end())
			io.AddKeyEvent(keyItr->second, true);
		keyId = Raylib::GetKeyPressed();
	}

	// look for any keys that were down last frame and see if they were down and are released
	for (const auto keyItr : RaylibKeyMap)
	{
		if (Raylib::IsKeyReleased(keyItr.first))
			io.AddKeyEvent(keyItr.second, false);
	}

	// add the text input in order
	unsigned int pressed = Raylib::GetCharPressed();
	while (pressed != 0)
	{
		io.AddInputCharacter(pressed);
		pressed = Raylib::GetCharPressed();
	}

    return true;
}