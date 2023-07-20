#pragma once

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnCircle(float radius);
	static sf::Vector2f RandomInCircle(float radius);
	static float RandomValue();

	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	static void SetOrigin(sf::Text& text, Origins origin);
	static void SetOrigin(sf::Shape& shape, Origins origin);
	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);

	static float Clamp(float v, float min, float max);
	static sf::Vector2f Clamp(const sf::Vector2f& v, const sf::Vector2f& min, const sf::Vector2f& max);

	static float Lerp(float a, float b, float t, bool clamping = true);
	static sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t, bool clamping = true);
	static sf::Color Lerp(const sf::Color& a, const sf::Color& b, float t, bool clamping = true);

	static const sf::Vector2f Normalize(const sf::Vector2f& vector);
	static float Magnitude(const sf::Vector2f& vector2);
	static float SqrMagnitude(const sf::Vector2f& vector);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	static float Angle(const sf::Vector2f& start, const sf::Vector2f& end);
	static float Angle(const sf::Vector2f& dir);

	static void FlipX(sf::Sprite& sprite, bool Flip);

	static sf::Vector2f GetSprite(const sf::Sprite& sprite);

	template <typename T, typename T1 = std::string, typename T2 = std::string>
	static std::vector<std::string> GetInfos(rapidcsv::Document& doc, T key, T1 key1 = "", T2 key2 = "");
};

template<typename T, typename T1, typename T2>
inline std::vector<std::string> Utils::GetInfos(rapidcsv::Document& doc, T key, T1 key1, T2 key2)
{
	std::vector<std::string> infos;
	std::cout << doc.GetRowCount() << std::endl;
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<T>(0, i) == key && doc.GetCell<T1>(1, i) == key1 && doc.GetCell<T2>(2, i) == key2)
		{
			for (int j = 3; j < doc.GetColumnCount(); j++)
			{
				infos.push_back(doc.GetCell<std::string>(j, i));
			}
			break;
		}
	}
	return infos;
}
