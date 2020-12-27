#ifndef EXAMPLE_UTIL_IMAGE_UTIL_H
#define EXAMPLE_UTIL_IMAGE_UTIL_H

#include <string>
#include <vector>

class image_sequence {
public:
    size_t done_count = 0;
    
    struct frame {
        frame(const std::string& img_path, const double timestamp)
            : img_path_(img_path), timestamp_(timestamp){};

        const std::string img_path_;
        const double timestamp_;
    };

    image_sequence(const std::string& img_dir_path, const double fps);

    virtual ~image_sequence() = default;

    std::vector<frame> get_frames();

    bool reload();

private:
    const double fps_;
    const std::string img_dir_path_;

    std::vector<std::string> img_file_paths_;
};

#endif // EXAMPLE_UTIL_IMAGE_UTIL_H
