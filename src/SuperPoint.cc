#include "SuperPoint.h"

namespace ORB_SLAM2
{
    const Options options;
    // options.optBatchSizes = { 2, 4, 6 };
    SuperPoint model_engine1(options);
    SuperPoint model_engine2(options);
    SuperPoint model_engine3(options);
    SuperPoint model_engine4(options);
    SuperPoint model_engine5(options);
    SuperPoint model_engine6(options);
    SuperPoint model_engine7(options);
    SuperPoint model_engine8(options);

    void NMS(cv::Mat det, cv::Mat conf, cv::Mat desc, std::vector<cv::KeyPoint> &pts, cv::Mat &descriptors,
             int border, int dist_thresh, int img_width, int img_height);
    void NMS2(std::vector<cv::KeyPoint> det, cv::Mat conf, std::vector<cv::KeyPoint> &pts,
              int border, int dist_thresh, int img_width, int img_height);

    SPDetector::SPDetector(std::shared_ptr<SuperPoint> _model_engine)
        : model_engine1(_model_engine),
          model_engine2(_model_engine),
          model_engine3(_model_engine),
          model_engine4(_model_engine),
          model_engine5(_model_engine),
          model_engine6(_model_engine),
          model_engine7(_model_engine),
          model_engine8(_model_engine)
    {
    }

    float getBilinearInterpolation(const cv::Mat &image, float x, float y)
    {
        int x1 = static_cast<int>(x);
        int y1 = static_cast<int>(y);
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        float dx = x - x1;
        float dy = y - y1;

        if (x2 >= image.size[1] || y2 >= image.size[0])
        {
            return 0.0; // Return 0 for out-of-bounds coordinates.
        }

        float value = (1.0 - dx) * (1.0 - dy) * image.at<float>(y1, x1) +
                      dx * (1.0 - dy) * image.at<float>(y1, x2) +
                      (1.0 - dx) * dy * image.at<float>(y2, x1) +
                      dx * dy * image.at<float>(y2, x2);

        return value;
    }

    void channelsLastToChannelsFirst(cv::Mat &input, cv::Mat &output)
    {
        // Check if the input has 128 channels
        if (input.size[0] != 128)
        {
            std::cerr << "Error: The input image must have 128 channels." << std::endl;
            return;
        }

        // Get the input image dimensions
        int height = input.size[1];
        int width = input.size[2];
        // Create a vector of cv::Mat objects (assuming 128 channels)
        std::vector<cv::Mat> channels(128, cv::Mat(height, width, CV_32FC1, cv::Scalar(0)));
        cv::Mat tmp_image;
        tmp_image = input.clone();
        for (int i = 0; i < 128; i++)
        {
            tmp_image({cv::Range(i, i + 1), cv::Range::all(), cv::Range::all()}).copyTo(channels[i]);
        }

        cv::merge(channels, output);
    }

    void SPDetector::detect(cv::Mat &img, bool cuda, int level)

    {

        std::vector<cv::Mat> images;
        std::vector<cv::Mat> featureVectors_descriptor;
        std::vector<cv::Mat> featureVectors_detector_rep;
        std::vector<cv::Mat> featureVectors_detector_rel;

        featureVectors_descriptor.clear();
        featureVectors_detector_rep.clear();
        featureVectors_detector_rel.clear();
        images.clear();
        // std::cout << "Image size: " << img.size() << std::endl;
        cv::Mat imgConvert;
        img.convertTo(imgConvert, CV_32F, 1.f / 255.f);
        // int width = img.cols;
        // int height = img.rows;
        // int width_c = width / 8;
        // int height_c = height / 8;
        // cv::Mat imgResized;
        // cv::resize(imgConvert, imgResized, cv::Size(width_c * 8, height_c * 8), cv::INTER_LINEAR);
        // std::cout << "Resized Image size: " << imgResized.size() << std::endl;
        //  cv::imshow("Input",imgResized);
        //  cv::waitKey(1);
        cv::Mat rgb;
        cv::cvtColor(imgConvert, rgb, cv::COLOR_GRAY2RGB);

        // cv::imshow("Input",imgConvert);
        // cv::waitKey(1);
        // std::cout << "Image size: " << rgb.size() << std::endl;

        images.push_back(rgb);
        bool succ;

        switch (level)
        {
        case 0:
        {
            succ = model_engine1->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 1:
        {
            succ = model_engine2->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 2:
        {
            succ = model_engine3->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 3:
        {
            succ = model_engine4->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 4:
        {
            succ = model_engine5->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 5:
        {
            succ = model_engine6->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 6:
        {
            succ = model_engine7->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        case 7:
        {
            succ = model_engine8->runInference(images, featureVectors_descriptor, featureVectors_detector_rep, featureVectors_detector_rel);
            if (!succ)
            {
                throw std::runtime_error("Unable to run semanticKeypoints inference.");
            }
            break;
        }
        }

        bool use_cuda = cuda && torch::cuda::is_available();
        torch::DeviceType device_type;
        if (use_cuda)
            device_type = torch::kCUDA;
        else
            device_type = torch::kCPU;
        torch::Device device(device_type);

        cv::Mat descriptorImg(3, featureVectors_descriptor[0].size, CV_32F, featureVectors_descriptor[0].data);
        cv::Mat detectorRep(2, featureVectors_detector_rep[0].size, CV_32F, featureVectors_detector_rep[0].data);
        cv::Mat detectorRel(2, featureVectors_detector_rel[0].size, CV_32F, featureVectors_detector_rel[0].data);

        // cv::resize(detectorRep, detectorRep, cv::Size(width, height), cv::INTER_LINEAR);
        // std::cout << detectorRel.size << std::endl;

        detectorRep = detectorRep.mul(detectorRel);
        mProb = detectorRep.clone();

        // cv::Mat output;
        // channelsLastToChannelsFirst(descriptorImg, output);
        // mDesc = output.clone();

        // mProb = torch::zeros({detectorRep.size[0], detectorRep.size[1]}, torch::kF32).to(device);
        // mProb = mProb.set_requires_grad(false);
        // std::memcpy(mProb.data_ptr(), featureVectors_detector_rep[0].data, sizeof(float) * mProb.numel());

        mDesc = torch::zeros({descriptorImg.size[0], descriptorImg.size[1], descriptorImg.size[2]}, torch::kF32).to(device);
        std::memcpy(mDesc.data_ptr(), descriptorImg.data, sizeof(float) * mDesc.numel());
        mDesc = mDesc.set_requires_grad(false);

        // torch::Tensor mDetectorRep = torch::zeros({detectorRep.size[0], detectorRep.size[1]}, torch::kF32).to(device);
        // torch::Tensor mDetectorRel = torch::zeros({detectorRel.size[0], detectorRel.size[1]}, torch::kF32).to(device);
        // mDetectorRep = mDetectorRep.set_requires_grad(false);
        // mDetectorRel = mDetectorRel.set_requires_grad(false);
        // std::memcpy(mDetectorRep.data_ptr(), featureVectors_detector_rep[0].data, sizeof(float) * mDetectorRep.numel());
        // std::memcpy(mDetectorRel.data_ptr(), featureVectors_detector_rel[0].data, sizeof(float) * mDetectorRep.numel());
        // mDetectorRep = mDetectorRep.unsqueeze(0);
        // torch::nn::MaxPool2d maxPool(torch::nn::MaxPool2dOptions(3).stride(1).padding(1));
        // auto maxRes = maxPool(mDetectorRep);
        // torch::Tensor maxima = (mDetectorRep == maxRes).to(torch::kFloat);
        // // maxima = maxima.squeeze(0);
        // mDetectorRel = mDetectorRel.unsqueeze(0);
        // maxima *= (mDetectorRep >= 0);
        // maxima *= (mDetectorRel >= 0);
        // maxima = maxima.squeeze(0);
        // // Convert PyTorch tensor to a contiguous tensor on CPU
        // torch::Tensor tensorCpu = maxima.to(torch::kCPU).contiguous();
        // // Extract the data pointer from the PyTorch tensor
        // float* tensorData = tensorCpu.data_ptr<float>();
        // // Create an OpenCV Mat object from the tensor data
        // cv::Mat mat(maxima.size(0), maxima.size(1), CV_32F, tensorData);
        // mProb = mat;
        mDesc = mDesc.unsqueeze(0);
    }

    /*void SPDetector::getKeyPoints(float threshold, int iniX, int maxX, int iniY, int maxY, std::vector<cv::KeyPoint> &keypoints, bool nms)
    {
        auto prob = mProb.slice(0, iniY, maxY).slice(1, iniX, maxX); // [h, w]
        auto kpts = (prob > threshold);
        kpts = torch::nonzero(kpts); // [n_keypoints, 2]  (y, x)
        std::vector<cv::KeyPoint> keypoints_no_nms;
        for (int i = 0; i < kpts.size(0); i++)
        {
            float response = prob[kpts[i][0]][kpts[i][1]].item<float>();
            keypoints_no_nms.push_back(cv::KeyPoint(kpts[i][1].item<float>(), kpts[i][0].item<float>(), 8, -1, response));
        }
        nms = false;
        if (nms)
        {
            cv::Mat conf(keypoints_no_nms.size(), 1, CV_32F);
            for (size_t i = 0; i < keypoints_no_nms.size(); i++)
            {
                int x = keypoints_no_nms[i].pt.x;
                int y = keypoints_no_nms[i].pt.y;
                conf.at<float>(i, 0) = prob[y][x].item<float>();
            }

            // cv::Mat descriptors;
            int border = 0;
            int dist_thresh = 4;
            int height = maxY - iniY;
            int width = maxX - iniX;

            NMS2(keypoints_no_nms, conf, keypoints, border, dist_thresh, width, height);
        }
        else
        {
            keypoints = keypoints_no_nms;
        }
    }*/

    void SPDetector::getKeyPoints(float threshold, int iniX, int maxX, int iniY, int maxY, std::vector<cv::KeyPoint> &keypoints, bool nms)
    {
        auto prob = mProb(cv::Range(iniY, maxY), cv::Range(iniX, maxX)).clone();
        cv::Mat kpts;
        cv::threshold(prob, kpts, threshold, 1, cv::THRESH_BINARY);
        // Find non-zero pixel locations
        std::vector<cv::Point> non_zero_pixels;
        cv::findNonZero(kpts, non_zero_pixels);

        std::vector<cv::KeyPoint> keypoints_no_nms;
        for (int i = 0; i < non_zero_pixels.size(); i++)
        {
            auto x = prob.clone();
            float response = x.at<float>(non_zero_pixels[i]);
            keypoints_no_nms.push_back(cv::KeyPoint(float(non_zero_pixels[i].x), float(non_zero_pixels[i].y), 8, -1, response));
        }
        nms = false;
        if (nms)
        {
            cv::Mat conf(keypoints_no_nms.size(), 1, CV_32F);
            for (size_t i = 0; i < keypoints_no_nms.size(); i++)
            {
                int x = keypoints_no_nms[i].pt.x;
                int y = keypoints_no_nms[i].pt.y;
                conf.at<float>(i, 0) = prob.at<float>(y, x);
                // std::cout << "*********conf: "<< conf.at<float>(i, 0) <<"x: "<< x<<" "<<"y: "<<y<< std::endl;
            }

            // cv::Mat descriptors;

            int border = 0;
            int dist_thresh = 4;
            int height = maxY - iniY;
            int width = maxX - iniX;

            NMS2(keypoints_no_nms, conf, keypoints, border, dist_thresh, width, height);
        }
        else
        {
            keypoints = keypoints_no_nms;
        }
    }

    void SPDetector::computeDescriptors(const std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
    {
        cv::Mat kpt_mat(keypoints.size(), 2, CV_32F); // [n_keypoints, 2]  (y, x)
        for (size_t i = 0; i < keypoints.size(); i++)
        {
            kpt_mat.at<float>(i, 0) = (float)keypoints[i].pt.y;
            kpt_mat.at<float>(i, 1) = (float)keypoints[i].pt.x;
        }
        auto fkpts = torch::from_blob(kpt_mat.data, {keypoints.size(), 2}, torch::kFloat);
        // std::cout << "Keypoints: " << keypoints.size() << std::endl;
        auto grid = torch::zeros({1, 1, fkpts.size(0), 2});                         // [1, 1, n_keypoints, 2]
        grid[0][0].slice(1, 0, 1) = 2.0 * fkpts.slice(1, 1, 2) / (mProb.size[1]-1) - 1; // x
        grid[0][0].slice(1, 1, 2) = 2.0 * fkpts.slice(1, 0, 1) / (mProb.size[0]-1) - 1; // y
        auto desc = torch::grid_sampler(mDesc, grid, 0, 0, false);                  // [1, 256, 1, n_keypoints]
        desc = desc.squeeze(0).squeeze(1);                                          // [256, n_keypoints]
        // normalize to 1
        auto dn = torch::norm(desc, 2, 1);
        desc = desc.div(torch::unsqueeze(dn, 1));
        desc = desc.transpose(0, 1).contiguous(); // [n_keypoints, 256]
        // desc = desc.to(torch::kCPU);

        cv::Mat desc_mat(cv::Size(desc.size(1), desc.size(0)), CV_32FC1, desc.data_ptr<float>());
        // std::cout << "desc_mat: " << desc_mat.size() << std::endl;
        descriptors = desc_mat.clone();
    }

    /*void SPDetector::computeDescriptors(const std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
    {
        cv::Mat kpt_mat(keypoints.size(), 2, CV_32F); // [n_keypoints, 2]  (y, x)
        //std::cout << "Keypoints: " << keypoints.size() << std::endl;
        for (size_t i = 0; i < keypoints.size(); i++)
        {
            kpt_mat.at<float>(i, 0) = (float)keypoints[i].pt.y;
            kpt_mat.at<float>(i, 1) = (float)keypoints[i].pt.x;
        }

        auto fkpts = kpt_mat.clone();
        int sizes[] = {fkpts.size[0], 2};
        cv::Mat grid = cv::Mat::zeros(2, sizes, CV_32F);
        // Compute the scaled and shifted version of the fkpts sub-tensors
        cv::Mat scaled_fkpts_x = 2.0 * fkpts.colRange(1, 2).clone() / mProb.size[1] - 1;
        cv::Mat scaled_fkpts_y = 2.0 * fkpts.colRange(0, 1).clone() / mProb.size[0] - 1;
        scaled_fkpts_x.copyTo(grid.col(0));
        scaled_fkpts_y.copyTo(grid.col(1));
        // Compute the output size of the grid sampling operation
        cv::Size output_size(grid.size[0], mDesc.channels());
        // Create a new matrix to hold the output of the grid sampling operation
        cv::Mat output(output_size, CV_32F, cv::Scalar(0));
        // Create a vector of cv::Mat objects (assuming 128 channels)
        int height = mDesc.size[0];
        int width = mDesc.size[1];
        std::vector<cv::Mat> channels(128, cv::Mat(height, width, CV_32FC1, cv::Scalar(0)));
        cv::Mat tmp_image;
        tmp_image = mDesc.clone();
        cv::split(tmp_image, channels);

        // Iterate over the output rows and columns
        for (int j = 0; j < grid.size[0]; j++)
        {
            // Compute the input row and column indices using the grid tensor
            //float input_y = (grid.at<cv::Vec2f>(cv::Point(j, 0))[1] + 1) * 0.5 * (mDesc.size[0] - 1);
            //float input_x = (grid.at<cv::Vec2f>(cv::Point(j, 0))[0] + 1) * 0.5 * (mDesc.size[1] - 1);
            float input_y = (grid.at<float>(j,1) + 1) * 0.5 * (mDesc.size[0] - 1);
            float input_x = (grid.at<float>(j,0) + 1) * 0.5 * (mDesc.size[1] - 1);
            //  Perform bilinear interpolation to compute the output value

            for (int i = 0; i < mDesc.channels(); i++)
            {

                cv::Mat rect = channels[i].clone();
                float value = getBilinearInterpolation(rect, input_x, input_y);
                output.at<float>(i, j) = value;
            }
        }

        // cv::Mat l2_norm_colwise(output.cols, 1, CV_32F);
        // for (int i = 0; i < output.cols; i++)
        // {
        //     l2_norm_colwise.at<float>(i, 0) = cv::norm(output.col(i), cv::NORM_L2);
        // }

        // // Normalize the input matrix col-wise
        // cv::Mat normalized(output.size(), output.type());
        // for (int i = 0; i < output.cols; i++)
        // {
        //     output.col(i).convertTo(normalized.col(i), -1, 1.0 / l2_norm_colwise.at<float>(i, 0));
        // }
        cv::Mat transposed;
        // cv::transpose(normalized, transposed);
        cv::transpose(output, transposed);
        descriptors = transposed.clone();
        //std::cout << descriptors.size() << std::endl;
    }*/

    /*void SPDetector::computeDescriptors(const std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
    {
        cv::Mat kpt_mat(keypoints.size(), 2, CV_32F); // [n_keypoints, 2]  (y, x)

        for (size_t i = 0; i < keypoints.size(); i++)
        {
            kpt_mat.at<float>(i, 0) = (float)keypoints[i].pt.y;
            kpt_mat.at<float>(i, 1) = (float)keypoints[i].pt.x;
        }

        auto fkpts = kpt_mat.clone();
        int sizes[] = {fkpts.size[0], 2};
        cv::Mat grid = cv::Mat::zeros(2, sizes, CV_32F);
        // Compute the scaled and shifted version of the fkpts sub-tensors
        cv::Mat scaled_fkpts_x = 2.0 * fkpts.colRange(1, 2).clone() / mProb.size[1] - 1;
        cv::Mat scaled_fkpts_y = 2.0 * fkpts.colRange(0, 1).clone() / mProb.size[0] - 1;

        scaled_fkpts_x.copyTo(grid.col(0));
        scaled_fkpts_y.copyTo(grid.col(1));
        // std::cout << grid << std::endl;
        //  Compute the output size of the grid sampling operation
        cv::Size output_size(grid.size[0], mDesc.channels());
        // Create a new matrix to hold the output of the grid sampling operation
        cv::Mat output(output_size, CV_32F, cv::Scalar(0));
        // Create a vector of cv::Mat objects (assuming 256 channels)
        int height = mDesc.size[0];
        int width = mDesc.size[1];
        std::vector<cv::Mat> channels(128, cv::Mat(height, width, CV_32F, cv::Scalar(0)));
        cv::Mat tmp_image;
        tmp_image = mDesc.clone();
        cv::split(tmp_image, channels);
        // Iterate over the output rows and columns
        for (int j = 0; j < grid.size[0]; j++)
        {
            // Compute the input row and column indices using the grid tensor
            float input_y = (grid.at<cv::Vec2f>(cv::Point(j, 0))[1] + 1) * 0.5 * (mDesc.rows - 1);
            float input_x = (grid.at<cv::Vec2f>(cv::Point(j, 0))[0] + 1) * 0.5 * (mDesc.cols - 1);
            // std::cout << input_y << " " << input_x << std::endl;

            // Perform bilinear interpolation to compute the output value
            cv::Size patch_size(1, 1);
            cv::Point2f patch_center(input_y, input_x);
            cv::Mat patch;
            for (int i = 0; i < mDesc.channels(); i++)
            {
                cv::getRectSubPix(channels[i], patch_size, patch_center, patch);
                output.at<float>(i, j) = patch.at<float>(0, 0);
            }
        }

        
        cv::Mat l2_norm_colwise(output.cols, 1, CV_32F);
        for (int i = 0; i < output.cols; i++) {
            l2_norm_colwise.at<float>(i, 0) = cv::norm(output.col(i), cv::NORM_L2);
        }

        // Normalize the input matrix col-wise
        cv::Mat normalized(output.size(), output.type());
        for (int i = 0; i < output.cols; i++) {
            output.col(i).convertTo(normalized.col(i), -1, 1.0 / l2_norm_colwise.at<float>(i,0));
        }
        cv::Mat transposed;
        cv::transpose(normalized, transposed);
        // cv::transpose(output, transposed);
        descriptors = transposed.clone();
    }*/

    void NMS2(std::vector<cv::KeyPoint> det, cv::Mat conf, std::vector<cv::KeyPoint> &pts,
              int border, int dist_thresh, int img_width, int img_height)
    {

        std::vector<cv::Point2f> pts_raw;

        for (int i = 0; i < det.size(); i++)
        {

            int u = (int)det[i].pt.x;
            int v = (int)det[i].pt.y;

            pts_raw.push_back(cv::Point2f(u, v));
        }

        cv::Mat grid = cv::Mat(cv::Size(img_width, img_height), CV_8UC1);
        cv::Mat inds = cv::Mat(cv::Size(img_width, img_height), CV_16UC1);

        cv::Mat confidence = cv::Mat(cv::Size(img_width, img_height), CV_32FC1);

        grid.setTo(0);
        inds.setTo(0);
        confidence.setTo(0);

        for (int i = 0; i < pts_raw.size(); i++)
        {
            int uu = (int)pts_raw[i].x;
            int vv = (int)pts_raw[i].y;

            grid.at<char>(vv, uu) = 1;
            inds.at<unsigned short>(vv, uu) = i;

            confidence.at<float>(vv, uu) = conf.at<float>(i, 0);
        }

        cv::copyMakeBorder(grid, grid, dist_thresh, dist_thresh, dist_thresh, dist_thresh, cv::BORDER_CONSTANT, 0);

        for (int i = 0; i < pts_raw.size(); i++)
        {
            int uu = (int)pts_raw[i].x + dist_thresh;
            int vv = (int)pts_raw[i].y + dist_thresh;

            if (grid.at<char>(vv, uu) != 1)
                continue;

            for (int k = -dist_thresh; k < (dist_thresh + 1); k++)
                for (int j = -dist_thresh; j < (dist_thresh + 1); j++)
                {
                    if (j == 0 && k == 0)
                        continue;

                    if (confidence.at<float>(vv + k, uu + j) < confidence.at<float>(vv, uu))
                        grid.at<char>(vv + k, uu + j) = 0;
                }
            grid.at<char>(vv, uu) = 2;
        }

        size_t valid_cnt = 0;
        std::vector<int> select_indice;

        for (int v = 0; v < (img_height + dist_thresh); v++)
        {
            for (int u = 0; u < (img_width + dist_thresh); u++)
            {
                if (u - dist_thresh >= (img_width - border) || u - dist_thresh < border || v - dist_thresh >= (img_height - border) || v - dist_thresh < border)
                    continue;

                if (grid.at<char>(v, u) == 2)
                {
                    int select_ind = (int)inds.at<unsigned short>(v - dist_thresh, u - dist_thresh);
                    cv::Point2f p = pts_raw[select_ind];
                    float response = conf.at<float>(select_ind, 0);
                    pts.push_back(cv::KeyPoint(p, 8.0f, -1, response));

                    select_indice.push_back(select_ind);
                    valid_cnt++;
                }
            }
        }

        // descriptors.create(select_indice.size(), 256, CV_32F);

        // for (int i=0; i<select_indice.size(); i++)
        // {
        //     for (int j=0; j < 256; j++)
        //     {
        //         descriptors.at<float>(i, j) = desc.at<float>(select_indice[i], j);
        //     }
        // }
    }

    void NMS(cv::Mat det, cv::Mat conf, cv::Mat desc, std::vector<cv::KeyPoint> &pts, cv::Mat &descriptors,
             int border, int dist_thresh, int img_width, int img_height)
    {

        std::vector<cv::Point2f> pts_raw;

        for (int i = 0; i < det.rows; i++)
        {

            int u = (int)det.at<float>(i, 0);
            int v = (int)det.at<float>(i, 1);
            // float conf = det.at<float>(i, 2);

            pts_raw.push_back(cv::Point2f(u, v));
        }

        cv::Mat grid = cv::Mat(cv::Size(img_width, img_height), CV_8UC1);
        cv::Mat inds = cv::Mat(cv::Size(img_width, img_height), CV_16UC1);

        cv::Mat confidence = cv::Mat(cv::Size(img_width, img_height), CV_32FC1);

        grid.setTo(0);
        inds.setTo(0);
        confidence.setTo(0);

        for (int i = 0; i < pts_raw.size(); i++)
        {
            int uu = (int)pts_raw[i].x;
            int vv = (int)pts_raw[i].y;

            grid.at<char>(vv, uu) = 1;
            inds.at<unsigned short>(vv, uu) = i;

            confidence.at<float>(vv, uu) = conf.at<float>(i, 0);
        }

        cv::copyMakeBorder(grid, grid, dist_thresh, dist_thresh, dist_thresh, dist_thresh, cv::BORDER_CONSTANT, 0);

        for (int i = 0; i < pts_raw.size(); i++)
        {
            int uu = (int)pts_raw[i].x + dist_thresh;
            int vv = (int)pts_raw[i].y + dist_thresh;

            if (grid.at<char>(vv, uu) != 1)
                continue;

            for (int k = -dist_thresh; k < (dist_thresh + 1); k++)
                for (int j = -dist_thresh; j < (dist_thresh + 1); j++)
                {
                    if (j == 0 && k == 0)
                        continue;

                    if (conf.at<float>(vv + k, uu + j) < conf.at<float>(vv, uu))
                        grid.at<char>(vv + k, uu + j) = 0;
                }
            grid.at<char>(vv, uu) = 2;
        }

        size_t valid_cnt = 0;
        std::vector<int> select_indice;

        for (int v = 0; v < (img_height + dist_thresh); v++)
        {
            for (int u = 0; u < (img_width + dist_thresh); u++)
            {
                if (u - dist_thresh >= (img_width - border) || u - dist_thresh < border || v - dist_thresh >= (img_height - border) || v - dist_thresh < border)
                    continue;

                if (grid.at<char>(v, u) == 2)
                {
                    int select_ind = (int)inds.at<unsigned short>(v - dist_thresh, u - dist_thresh);
                    pts.push_back(cv::KeyPoint(pts_raw[select_ind], 1.0f));

                    select_indice.push_back(select_ind);
                    valid_cnt++;
                }
            }
        }

        descriptors.create(select_indice.size(), 128, CV_32F);

        for (int i = 0; i < select_indice.size(); i++)
        {
            for (int j = 0; j < 128; j++)
            {
                descriptors.at<float>(i, j) = desc.at<float>(select_indice[i], j);
            }
        }
    }

} // namespace ORB_SLAM
