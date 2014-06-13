using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace e57_metadata_wrapper {
    class e57_metadata_wrapper {
        [DllImport("e57_metadata.dll")]
        public static extern int extract(string input_file, string output_file, string file_type);

        static public bool extract_metadata(string input_file, string output_file, string file_type) {
            int result = extract(input_file, output_file, file_type);
            return result == 0;
        }
    }
}
