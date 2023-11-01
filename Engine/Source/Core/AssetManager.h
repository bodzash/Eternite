#pragma once
#include "Core.h"
#include "Log.h"
#include <unordered_map>

namespace Apex {

    template<typename T>
    class AssetManager
    {
    public:
        void Load(const std::string& name, Ref<T> asset)
        {
            if (Exists(name))
            {
                AX_CORE_WARN("Asset '{0}' already exists...", name);
            }

            m_Assets[name] = asset;
        }

        Ref<T> Get(const std::string& name)
        {
            if (Exists(name))
            {
                return m_Assets[name];
            }
            else
            {
                AX_CORE_ERROR("Asset '{0}' doesn't exists...", name);
                return nullptr;
            }
        }

        void Delete(const std::string& name)
        {
            if (Exists(name))
            {
                // NOTE: destructors of assets should handle actual Unloading of themselves
                auto it = m_Assets.find(name);
                auto useCount = it->second.use_count();
                if (useCount > 1)
                {
                    AX_CORE_INFO("AssetManager::Deleted: {0}, remaining handles: {1}", name, useCount);
                }
                m_Assets.erase(it);
            }
        }

        void Clear()
        {
            m_Assets.clear();
        }

        bool Exists(const std::string& name)
        {
            return m_Assets.find(name) != m_Assets.end();
        }

    private:
        std::unordered_map<std::string, Ref<T>> m_Assets;
    };

}
