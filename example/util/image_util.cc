#include "image_util.h"

#include <dirent.h>
#include <algorithm>
#include <sstream>
#include <stdexcept>

image_sequence::image_sequence(const std::string& img_dir_path, const double fps)
    : fps_(fps), img_dir_path_(img_dir_path) {
    reload();
}

std::vector<image_sequence::frame> image_sequence::get_frames() {
    std::vector<frame> frames;
    for (unsigned int i = done_count; i < img_file_paths_.size(); ++i) {
        std::string path = img_file_paths_.at(i);
        size_t st_pos = path.find_last_of('/');
        if (st_pos == std::string::npos) st_pos = 0;
        else st_pos ++;
        size_t end_pos = path.find_last_of('.');
        if (end_pos == std::string::npos) end_pos = path.size();
        std::stringstream ss(path.substr(st_pos, end_pos - st_pos));
        double timestamp = (1.0 / fps_) * i;
        ss >> timestamp;
        
        frames.emplace_back(frame{path, timestamp});
    }
    return frames;
}

bool image_sequence::reload() {
    done_count = img_file_paths_.size();
    img_file_paths_.clear();

    DIR* dir;
    if ((dir = opendir(img_dir_path_.c_str())) == nullptr) {
        throw std::runtime_error("directory " + img_dir_path_ + " does not exist");
    }
    dirent* dp;
    for (dp = readdir(dir); dp != nullptr; dp = readdir(dir)) {
        const std::string img_file_name = dp->d_name;
        if (img_file_name == "." || img_file_name == "..") {
            continue;
        }
        img_file_paths_.push_back(img_dir_path_ + "/" + img_file_name);
    }
    closedir(dir);

    std::sort(img_file_paths_.begin(), img_file_paths_.end());

    return img_file_paths_.size() > done_count;
}
