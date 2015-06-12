#include <iostream>
#include <algorithm>
#include <string>
#include <e57_metadata/e57_metadata.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
	fs::path  input_path;
	fs::path  output_path;
    std::string format;

	po::options_description desc("Graphene command line options");
	desc.add_options()
		("help,h",  "Help message")
		("input,i", po::value<fs::path>(&input_path) ->required(), "Input .e57 file")
		("output,o", po::value<fs::path>(&output_path) ->required(), "Output file")
		("format,f", po::value<std::string>(&format) ->default_value("JSON"), "Output file format (either \"JSON\" (default) or \"XML\")")
	;
	// Check for required options.
	po::variables_map vm;
	bool optionsException = false;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	} catch (std::exception& e) {
		if (!vm.count("help")) {
			std::cout << e.what() << "\n";
		}
		optionsException = true;
	}
	if (optionsException || vm.count("help")) {
		std::cout << desc << "\n";
		return optionsException ? 1 : 0;
	}

    std::string fmt;
    if (format == "JSON") {
        fmt = "json";
    } else if (format == "XML") {
        fmt = "xml";
    } else {
        std::cout << "Wrong format specifier. Must be either \"XML\" or \"JSON\"." << "\n";
        return 1;
    }

    if (!fs::exists(input_path)) {
        std::cout << "Input file \"" << input_path << "\" does not exist." << "\n";
        return 1;
    }

    std::string ext = input_path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext != ".e57") {
        std::cout << "Wrong file extension for input file. Must be \".e57\" or \".E57\"." << "\n";
        return 1;
    }

	return extract(input_path.string().c_str(), output_path.string().c_str(), fmt.c_str()) == 1;
}
