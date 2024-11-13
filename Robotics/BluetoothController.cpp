#include <libevdev/libevdev.h>
#include <iostream>

int main() {
    struct libevdev *dev = nullptr;
    int fd = -1;

    // Open the input device
    fd = open("/dev/input/eventX", O_RDONLY);
    if (fd < 0) {
        std::cerr << "Failed to open the input device." << std::endl;
        return 1;
    }

    // Initialize the libevdev device
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        std::cerr << "Failed to initialize libevdev." << std::endl;
        close(fd);
        return 1;
    }

    // Print device information
    std::cout << "Device: " << libevdev_get_name(dev) << std::endl;

    // Loop to read events
    while (true) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == LIBEVDEV_READ_STATUS_SUCCESS) {
            if (ev.type == EV_ABS) {
                std::cout << "Axis " << ev.code << ": " << ev.value << std::endl;
            } else if (ev.type == EV_KEY) {
                std::cout << "Button " << ev.code << ": " << ev.value << std::endl;
            }
        } else if (rc == LIBEVDEV_READ_STATUS_SYNC) {
            std::cerr << "Event sync occurred." << std::endl;
        } else if (rc == -EAGAIN) {
            // No events available, continue looping
        } else {
            std::cerr << "Failed to read event." << std::endl;
            break;
        }
    }

    // Release resources
    libevdev_free(dev);
    close(fd);

    return 0;
}
