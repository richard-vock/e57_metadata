#ifndef DURAARK_DATA_TYPES_HPP_
#define DURAARK_DATA_TYPES_HPP_

#include "libe57_serialize.hpp"

namespace duraark {

struct e57_scan_metadata_t {
	std::string                            name;
	std::string 	                       guid;
	std::vector<std::string>               original_guids;
	std::string                            description;
	std::string 	                       sensor_vendor;
	std::string 	                       sensor_model;
	std::string 	                       sensor_serial_number;
	std::string 	                       sensor_hardware_version;
	std::string 	                       sensor_software_version;
	std::string 	                       sensor_firmware_version;
	float 	                               temperature;
	float 	                               relative_humidity;
	float 	                               atmospheric_pressure;
	e57::DateTime                          acquisition_start;
	e57::DateTime                          acquisition_end;
	e57::RigidBodyTransform 	           pose;
	e57::IndexBounds 	                   index_bounds;
	e57::CartesianBounds                   cartesian_bounds;
	e57::SphericalBounds                   spherical_bounds;
	e57::IntensityLimits                   intensity_limits;
	e57::ColorLimits                       color_limits;
	e57::PointStandardizedFieldsAvailable  point_fields;
	int64_t 	                           points_size;
	

	template <class Archive>
	void serialize(Archive& ar) {
		ar(cereal::make_nvp("name", name),
			cereal::make_nvp("guid", guid),
			cereal::make_nvp("original_guids", original_guids),
			cereal::make_nvp("description", description),
			cereal::make_nvp("sensor_vendor", sensor_vendor),
			cereal::make_nvp("sensor_model", sensor_model),
			cereal::make_nvp("sensor_serial_number", sensor_serial_number),
			cereal::make_nvp("sensor_hardware_version", sensor_hardware_version),
			cereal::make_nvp("sensor_software_version", sensor_software_version),
			cereal::make_nvp("sensor_firmware_version", sensor_firmware_version),
			cereal::make_nvp("temperature", temperature),
			cereal::make_nvp("relative_humidity", relative_humidity),
			cereal::make_nvp("atmospheric_pressure", atmospheric_pressure),
			cereal::make_nvp("acquisition_start", acquisition_start),
			cereal::make_nvp("acquisition_end", acquisition_end),
			cereal::make_nvp("pose", pose),
			cereal::make_nvp("index_bounds", index_bounds),
			cereal::make_nvp("cartesian_bounds", cartesian_bounds),
			cereal::make_nvp("spherical_bounds", spherical_bounds),
			cereal::make_nvp("intensity_limits", intensity_limits),
			cereal::make_nvp("color_limits", color_limits),
			cereal::make_nvp("point_fields", point_fields),
			cereal::make_nvp("points_size", points_size));
	}
};

struct e57_metadata_t {
	std::string guid;
	uint32_t version_major;
	uint32_t version_minor;
	e57::DateTime creation_datetime;
	std::string coord_metadata;
	uint32_t scan_count;
	uint32_t image_count;
	uint32_t scan_size;
	uint32_t image_size;
	std::vector<e57_scan_metadata_t> scans;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(cereal::make_nvp("guid", guid),
		   cereal::make_nvp("version_major", version_major),
		   cereal::make_nvp("version_minor", version_minor),
		   cereal::make_nvp("creation_datetime", creation_datetime),
		   cereal::make_nvp("coordinate_metadata", coord_metadata),
		   cereal::make_nvp("scan_count", scan_count),
		   cereal::make_nvp("image_count", image_count),
		   cereal::make_nvp("scan_size", scan_size),
		   cereal::make_nvp("image_size", image_size),
		   cereal::make_nvp("scans", scans));
	}

	/*
	void serialize_csv(std::ofstream& out) {
		int year, month, day, hour, minute;
		float seconds;
		creation_datetime.GetUTCDateTime(year, month, day, hour, minute, seconds);

		// description
		out << "guid, ";
		out << "version_major, ";
		out << "version_minor, ";
		out << "creation_datetime, ";
		out << "coordinate_metadata, ";
		out << "scan_count";
		out << "\n";
		// data
		out << "\"" << guid << "\", ";
		out << version_major << ", ";
		out << version_minor << ", ";
		out << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << seconds << ", ";
		out << coord_metadata << ", ";
		out << scan_count << ", ";
		out << image_count << ", ";
		out << scan_size << ", ";
		out << image_size << "";
		out << "\n";
	}
	*/
};

}

#endif // DURAARK_DATA_TYPES_HPP_