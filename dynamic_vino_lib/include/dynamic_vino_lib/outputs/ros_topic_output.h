/*
 * Copyright (c) 2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @brief A header file with declaration for RosTopicOutput Class
 * @file ros_topic_output.h
 */

#ifndef DYNAMIC_VINO_LIB_OUTPUTS_ROS_TOPIC_OUTPUT_H
#define DYNAMIC_VINO_LIB_OUTPUTS_ROS_TOPIC_OUTPUT_H

#include <image_transport/image_transport.h>
#include <object_msgs/Object.h>
#include <object_msgs/ObjectInBox.h>
#include <object_msgs/ObjectsInBoxes.h>
#include <people_msgs/AgeGender.h>
#include <people_msgs/AgeGenderStamped.h>
#include <people_msgs/Emotion.h>
#include <people_msgs/EmotionsStamped.h>
#include <people_msgs/HeadPose.h>
#include <people_msgs/HeadPoseStamped.h>
#include <people_msgs/ObjectInMask.h>
#include <people_msgs/ObjectsInMasks.h>
#include <people_msgs/Reidentification.h>
#include <people_msgs/ReidentificationStamped.h>
#include <people_msgs/PersonAttribute.h>
#include <people_msgs/PersonAttributeStamped.h>
#include <people_msgs/VehicleAttribsStamped.h>
#include <people_msgs/VehicleAttribs.h>
#include <people_msgs/LicensePlateStamped.h>
#include <people_msgs/LicensePlate.h>
#include <people_msgs/Landmark.h>
#include <people_msgs/LandmarkStamped.h>
#include <ros/ros.h>

#include <memory>
#include <string>
#include <vector>

#include "dynamic_vino_lib/inferences/face_detection.h"
#include "dynamic_vino_lib/outputs/base_output.h"

namespace Outputs
{
/**
 * @class RosTopicOutput
 * @brief This class handles and publish the detection result with ros topic.
 */
class RosTopicOutput : public BaseOutput
{
public:
  RosTopicOutput(){};
  RosTopicOutput(std::string pipeline_name);
  /**
   * @brief Calculate the camera matrix of a frame.
   * @param[in] A frame.
   */
  void feedFrame(const cv::Mat&) override;
  /**
   * @brief Publish all the detected infomations generated by the accept
   * functions with ros topic.
   */
  void handleOutput() override;
  /**
   * @brief Generate image window output content according to
   * the license plate detection result.
   * @param[in] A license plate detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::LicensePlateDetectionResult>&) override;
  /**
   * @brief Generate image window output content according to
   * the vehicle attributes detection result.
   * @param[in] A vehicle attributes detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::VehicleAttribsDetectionResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the person attributes detection result.
   * @param[in] results a bundle of person attributes detection results.
   */
  void accept(const std::vector<dynamic_vino_lib::PersonAttribsDetectionResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the landmark detection result.
   * @param[in] results a bundle of person landmarks detection result.
   */
  void accept(const std::vector<dynamic_vino_lib::LandmarksDetectionResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the face reidentification result.
   * @param[in] results a bundle of face reidentification results.
   */
  void accept(const std::vector<dynamic_vino_lib::FaceReidentificationResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the person reidentification result.
   * @param[in] results a bundle of person reidentification results.
   */
  void accept(const std::vector<dynamic_vino_lib::PersonReidentificationResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the object segmentation result.
   * @param[in] results a bundle of object segmentation results.
   */
  void accept(const std::vector<dynamic_vino_lib::ObjectSegmentationResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the face detection result.
   * @param[in] An face detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::FaceDetectionResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the emotion detection result.
   * @param[in] An emotion detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::EmotionsResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the age gender detection result.
   * @param[in] An age gender detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::AgeGenderResult>&) override;
  /**detected_objects_topic_
   * @brief Generate ros topic infomation according to
   * the headpose detection result.
   * @param[in] An head pose detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::HeadPoseResult>&) override;
  /**
   * @brief Generate ros topic infomation according to
   * the headpose detection result.
   * @param[in] An head pose detection result objetc.
   */
  void accept(const std::vector<dynamic_vino_lib::ObjectDetectionResult>&) override;

private:
  std_msgs::Header getHeader();
  const std::string pipeline_name_;
  const std::string topic_name_;
  cv::Mat frame_;
  ros::NodeHandle nh_;

protected:
  ros::Publisher pub_face_;
  std::shared_ptr<object_msgs::ObjectsInBoxes> faces_topic_;
  ros::Publisher pub_emotion_;
  std::shared_ptr<people_msgs::EmotionsStamped> emotions_topic_;
  ros::Publisher pub_age_gender_;
  std::shared_ptr<people_msgs::AgeGenderStamped> age_gender_topic_;
  ros::Publisher pub_headpose_;
  std::shared_ptr<people_msgs::HeadPoseStamped> headpose_topic_;
  ros::Publisher pub_object_;
  std::shared_ptr<object_msgs::ObjectsInBoxes> detected_objects_topic_;
  ros::Publisher pub_person_reid_;
  std::shared_ptr<people_msgs::ReidentificationStamped> person_reid_topic_;
  ros::Publisher pub_segmented_object_;
  std::shared_ptr<people_msgs::ObjectsInMasks> segmented_objects_topic_;
  ros::Publisher pub_face_reid_;
  std::shared_ptr<people_msgs::ReidentificationStamped> face_reid_topic_;
  ros::Publisher pub_person_attribs_;
  std::shared_ptr<people_msgs::PersonAttributeStamped> person_attribs_topic_;
  ros::Publisher pub_license_plate_;
  std::shared_ptr<people_msgs::LicensePlateStamped> license_plate_topic_;
  ros::Publisher pub_vehicle_attribs_;
  std::shared_ptr<people_msgs::VehicleAttribsStamped> vehicle_attribs_topic_;
  ros::Publisher pub_landmarks_;
  std::shared_ptr<people_msgs::LandmarkStamped> landmarks_topic_;
};
}  // namespace Outputs
#endif  // DYNAMIC_VINO_LIB_OUTPUTS_ROS_TOPIC_OUTPUT_H
