import os
import sys

def embed_resources(resource_dir, header_file, source_file):
    with open(header_file, 'w') as header_file:
        header_file.write("#ifndef EMBEDDED_RESOURCES_H\n")
        header_file.write("#define EMBEDDED_RESOURCES_H\n\n")

        for root, _, files in os.walk(resource_dir):
            for file in files:
                array_name = file.replace(".", "_")

                if file.endswith((".png", ".jpg", ".bmp")):
                    header_file.write(f"extern const unsigned char {array_name}[];\n")
                    header_file.write(f"extern const unsigned int {array_name}_size;\n\n")

                if file.endswith((".vert", ".frag")):
                    header_file.write(f"extern const char {array_name}[];\n")
                    header_file.write(f"extern const unsigned int {array_name}_size;\n\n")

        header_file.write("#endif // EMBEDDED_RESOURCES_H\n")

    with open(source_file, 'w') as source_file:
        source_file.write(f'#include "{os.path.basename(header_file.name)}"\n\n')

        for root, _, files in os.walk(resource_dir):
            for file in files:
                file_path = os.path.join(root, file)
                array_name = file.replace(".", "_")

                if file.endswith((".png", ".jpg", ".bmp")):
                    source_file.write(f"const unsigned char {array_name}[] = {{\n")

                    with open(file_path, "rb") as binary_file:
                        bytes_read = binary_file.read()
                        for byte in bytes_read:
                            source_file.write(f"0x{byte:02x}, ")

                    source_file.write("\n};\n\n")
                    source_file.write(f"const unsigned int {array_name}_size = sizeof({array_name});\n\n")

                if file.endswith((".vert", ".frag")):
                    source_file.write(f"const char {array_name}[] = \n\"")

                    with open(file_path, "r") as text_file:
                        content = text_file.read().replace("\n", "\\n\"\n\"").replace("\"", "\\\"")
                        source_file.write(content)

                    source_file.write("\\n\";\n\n")
                    source_file.write(f"const unsigned int {array_name}_size = sizeof({array_name}) - 1;\n\n")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: embed_resources.py <resource_dir> <header_file> <source_file>")
        sys.exit(1)

    resource_dir = sys.argv[1]
    header_file = sys.argv[2]
    source_file = sys.argv[3]

    embed_resources(resource_dir, header_file, source_file)
