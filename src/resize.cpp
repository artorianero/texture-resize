#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../third_party/CLI11.hpp"

/**
 * Combine directory and filename into fullpath
 */
char* CombinePath(const char* dir, const char* fileName) {
    char* fullPath = new char[1024];
    strcpy(fullPath, dir);
    if (dir[strlen(dir) - 1] != '/') {
        strcat(fullPath, "/");
    }
    strcat(fullPath, fileName);
    // std::cout << "fullPath: " << fullPath << std::endl;

    return fullPath;
}

/**
 * Create floder if folder not exist
 */
void CheckFolder(const char* dir) {
    DIR* folder = opendir(dir);
    if (folder != NULL) {
        std::cout << "folder exists: " << dir << std::endl;
        return;
    } else {
        if (mkdir(dir, S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO) == 0) {
            std::cout << "create floder: " << dir << std::endl;
        }
    }
}

void resize(std::string input, std::string output) {
    cv::Mat image;
    std::vector<cv::String> filename;
    cv::glob(input, filename, false);
    size_t count = filename.size();

    CheckFolder(output.c_str());

    for (int i = 0; i < count; i++) {
        std::cout << "filename[i]: " << filename[i] << std::endl;

        // Get short filename
        std::string::size_type iPos = filename[i].find_last_of('/') + 1;
        std::string shortName = filename[i].substr(iPos, filename[i].length() - iPos);

        image = cv::imread(filename[i]);
        if (!image.data) {
            std::cout << "  -- Image reading error,escape this file."
                      << std::endl;
            continue;
        }

        // calculate new ize
        std::cout << "  -- raw size: " << image.size() << std::endl;
        int longSide = image.size().width > image.size().height
                           ? image.size().width
                           : image.size().height;
        int targetSize = 1024;
        for (; longSide < targetSize;) {
            targetSize = targetSize >> 1;
            if (targetSize == 1) {
                break;
            }
        }
        printf("  -- resize: [%d x %d]\n", targetSize, targetSize);

        // resize
        cv::Size dsize = cv::Size(targetSize, targetSize);
        cv::Mat shrink;
        resize(image, shrink, dsize, 0, 0, cv::INTER_AREA);

        // 保存
        // std::stringstream outPath;
        // outPath << output << shortName;
        char* outPath = CombinePath(output.c_str(), shortName.c_str());
        std::cout << "  -- ouput: " << outPath << std::endl;
        imwrite(outPath, shrink);
    }
}

int main(int argc, char** argv) {
    CLI::App app{"TEXTURE RESIZE v0.1"};
    // Descript parameters
    std::string input;
    std::string output = "./out/";
    // Add flag
    app.add_option("-i,--input", input, "输入图片的目录")->check(CLI::ExistingDirectory);
    app.add_option("-o,--output", output, "输入图片的目录");

    CLI11_PARSE(app, argc, argv);

    std::cout << "input: " << input << std::endl;
    std::cout << "output: " << output << std::endl;

    resize(input.c_str(), output.c_str());
}