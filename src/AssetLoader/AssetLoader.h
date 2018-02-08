#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <algorithm>

template <typename T>
struct Asset
{
	bool Load(const std::string& path)
	{
		return false;
	}

	T* Get()
	{
		return nullptr;
	}
};

template <>
struct Asset<sf::Texture>
{
	bool Load(const std::string& path)
	{
		return m_Texture.loadFromFile(path);
	}

	sf::Texture* Get()
	{
		return &m_Texture;
	}
private:
	sf::Texture m_Texture;
};

template <>
struct Asset<sf::Font>
{
	bool Load(const std::string& path)
	{
		return m_Font.loadFromFile(path);
	}

	sf::Font* Get()
	{
		return &m_Font;
	}
private:
	sf::Font m_Font;
};

template <typename T>
class AssetLoader
{
public:
	static AssetLoader<T>& GetInstance()
	{
		static AssetLoader<T> AssetLoader;
		return AssetLoader;
	}

	bool LoadAsset(const std::string& assetFile)
	{
		auto asset = "assets/" + assetFile;
		if (assetFile.size() >= 2 && assetFile[1] == ':') asset = assetFile;
		return m_Assets[asset].Load(asset);
	}

	T* Get(const std::string& key)
	{
		auto asset = "assets/" + key;
		if (key.size() >= 2 && key[1] == ':') asset = key;
		if (m_Assets.find(asset) != m_Assets.end()) return m_Assets[asset].Get();
		return nullptr;
	}
private:
	std::unordered_map <std::string, Asset<T>> m_Assets;
};