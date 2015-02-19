#include "formats/arc/nsa_archive.h"
#include "string/zlib.h"
#include "test_support/archive_support.h"

void test_nsa_archive_uncompressed()
{
    std::unique_ptr<File> file1(new File);
    std::unique_ptr<File> file2(new File);
    file1->name = "abc.txt";
    file2->name = "another.txt";
    file1->io.write("123", 3);
    file2->io.write("abcdefghij", 10);
    std::vector<File*> expected_files { file1.get(), file2.get() };

    std::string path = "tests/test_files/arc/nsa/uncompressed.nsa";
    std::unique_ptr<Archive> archive(new NsaArchive);
    auto output_files = unpack_to_memory(path, *archive);
    auto actual_files = output_files->get_saved();

    compare_files(expected_files, actual_files);
}

void test_nsa_archive_lzss()
{
    std::unique_ptr<File> file(new File);
    file->name = "test.bmp";
    file->io.write(zlib_inflate(std::string(
        "\x78\xDA\x8D\xD3\x3D\x6E\x13\x40\x10\x86\xE1\xB5\x44\x81\x70\x9C"
        "\x38\xF1\x25\xA8\x53\x50\x20\x2A\x8A\xE9\xB8\xD4\x9C\x69\x6E\x40"
        "\x9D\x1B\xCC\x11\xF2\xE7\x38\xB4\x63\x1E\x82\xA0\xCE\x4A\x9F\x56"
        "\x7A\xB7\x79\x9A\xFD\xFE\xE3\xEB\x87\xF5\x76\xBE\xB8\x3F\xBB\x37"
        "\xFF\xF7\xF1\xAD\xFF\x79\x3E\x6C\xFF\xEE\xDF\xE3\xB7\xDB\x4F\xEB"
        "\xBD\x67\xBB\xDD\xAE\x8B\x8B\x8B\xB5\xDB\xED\xD6\xE5\xE5\xE5\xBA"
        "\xBA\xBA\x5A\xFB\xFD\x7E\x5D\x5F\x5F\xAF\x9B\x9B\x9B\x75\x38\x1C"
        "\xD6\x66\xB3\xB1\xB0\xB4\xB2\xB6\x59\x9B\xD0\x43\x0F\x3D\xF4\xD0"
        "\x43\x4F\x3D\xF5\xD4\x53\x4F\x3D\xF5\xD2\x4B\x2F\xBD\xF4\xD2\x4B"
        "\x6F\xBD\xF5\xD6\x5B\x6F\xBD\xF5\xD1\x47\x1F\x7D\xF4\xD1\x67\x56"
        "\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0"
        "\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04"
        "\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F"
        "\xF0\x04\x4F\xF0\x04\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2"
        "\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24"
        "\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F"
        "\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF1\x14\x4F\xF1"
        "\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14"
        "\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F"
        "\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1"
        "\x14\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34"
        "\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F"
        "\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3"
        "\x34\x4F\xF3\x34\x4F\xF3\x34\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C"
        "\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF"
        "\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0"
        "\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xFD\xFD"
        "\xFD\x7A\x78\x78\x58\x8F\x8F\x8F\xEB\xE9\xE9\x69\x3D\x3F\x3F\xAF"
        "\xE3\xF1\xB8\x5E\x5E\x5E\xD6\xE9\x74\x5A\xAF\xAF\xAF\xEB\x7C\x3E"
        "\xBF\xEB\x3F\xFF\xBC\xFB\xB5\xEE\xDC\xBF\x01\x89\x72\x8B\xEC",
        479)));
    std::vector<File*> expected_files { file.get() };

    std::string path = "tests/test_files/arc/nsa/lzss.nsa";
    std::unique_ptr<Archive> archive(new NsaArchive);
    auto output_files = unpack_to_memory(path, *archive);
    auto actual_files = output_files->get_saved();

    compare_files(expected_files, actual_files);
}

int main(void)
{
    test_nsa_archive_uncompressed();
    test_nsa_archive_lzss();
    return 0;
}
