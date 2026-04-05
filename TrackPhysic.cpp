#include "TrackPhysic.h"

TrackPhysic::TrackPhysic(const std::string& path) {
	if (!trackMask.loadFromFile(path)) {
		throw std::runtime_error("Failed to load track mask: " + path);
	}
}

bool TrackPhysic::isOnTrack(sf::Vector2f position) const {
	// Ensure the position is within the bounds of the track mask
	if (position.x < 0 || position.y < 0 || 
		position.x >= trackMask.getSize().x || 
		position.y >= trackMask.getSize().y) {
		return false;
	}
	
	sf::Vector2u pixelPos(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y));
	sf::Color pixelColor = trackMask.getPixel(pixelPos);

	// Tam olarak sf::Color::White (255, 255, 255) kontrolü yapmak, fırça yumuşaklığı (anti-aliasing)
	// veya resim formatındaki ufak renk/alfa değişikliklerinden dolayı sorun çıkarabilir.
	// Bu yüzden parlaklık (örneğin kırmızı kanalının 128'den büyük olması) üzerinden eşik değeri ile kontrol ediyoruz.
	return pixelColor.r > 128;
}