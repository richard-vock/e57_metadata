using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using e57_metadata_wrapper;

namespace e57_metadata_wrapper {
    class Program {
        static void Main(string[] args) {
            if (args.Length < 2 || args.Length > 3) {
                System.Console.Out.WriteLine("%s", "Usage: e57_metadata_wrapper input_file.e57 output_file.ext [{json|xml}]");
            }
            string file_type = args.Length > 2 ? args[2] : "json";
            if (e57_metadata_wrapper.extract_metadata(args[0], args[1], file_type))
            {
                System.Console.Out.WriteLine("%s", "Successfully wrote "+file_type+" metadata file.");
            }
        }
    }
}
