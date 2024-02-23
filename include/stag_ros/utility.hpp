#pragma once

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/image_encodings.hpp>

namespace stag_ros {

// Read image from msg and convert it to grayscale, checks provided for rgb8
// and bgr8, default to mono8
inline bool msgToGray(const sensor_msgs::msg::Image::ConstSharedPtr &msg, cv::Mat &gray) {
  if (msg->encoding.compare("bgr8") == 0 || msg->encoding == sensor_msgs::image_encodings::BGRA8) {
    cv::Mat src = cv_bridge::toCvShare(msg, msg->encoding)->image;
    cv::cvtColor(src, gray, cv::COLOR_BGRA2GRAY);
    return true;
  } else if (msg->encoding.compare("rgb8") == 0) {
    cv::Mat src = cv_bridge::toCvShare(msg, msg->encoding)->image;
    cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    return true;
  } else if (msg->encoding.compare("mono8") == 0) {
    gray = cv_bridge::toCvShare(msg, msg->encoding)->image;
    return true;
  }
  return false;
}

}  // namespace stag_ros
