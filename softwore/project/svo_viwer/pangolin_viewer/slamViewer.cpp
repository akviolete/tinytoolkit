#include "slamViewer.h"

#include <string>

namespace pangolin_viewer
{

    viewer::viewer(const YAML::Node &yaml_node_)
            :
            interval_ms_(1000.0f / yaml_node_["PangolinViewer.fps"].as<float>(30.0)),
            viewpoint_x_(yaml_node_["PangolinViewer.viewpoint_x"].as<float>(0.0)),
            viewpoint_y_(yaml_node_["PangolinViewer.viewpoint_y"].as<float>(-10.0)),
            viewpoint_z_(yaml_node_["PangolinViewer.viewpoint_z"].as<float>(-0.1)),
            viewpoint_f_(yaml_node_["PangolinViewer.viewpoint_f"].as<float>(2000.0)),
            keyfrm_size_(yaml_node_["PangolinViewer.keyframe_size"].as<float>(0.1)),
            keyfrm_line_width_(yaml_node_["PangolinViewer.keyframe_line_width"].as<unsigned int>(1)),
            graph_line_width_(yaml_node_["PangolinViewer.graph_line_width"].as<unsigned int>(1)),
            point_size_(yaml_node_["PangolinViewer.point_size"].as<unsigned int>(2)),
            camera_size_(yaml_node_["PangolinViewer.camera_size"].as<float>(0.15)),
            camera_line_width_(yaml_node_["PangolinViewer.camera_line_width"].as<unsigned int>(2)),
            cs_(yaml_node_["PangolinViewer.color_scheme"].as<std::string>("black")),
            mapping_mode_(true),
            loop_detection_mode_(true)
    {

        viewpoint_x_ = 0;
        viewpoint_y_ = -0.7;
        viewpoint_z_ = -1.8;
        viewpoint_f_ = 500;

        keyfrm_size_ = 0.05;
        keyfrm_line_width_ = 1.0;
        camera_size_ = 0.08;
        camera_line_width_ = 2.0;

        point_size_ = 5.0;
    }

    void viewer::run()
    {
        is_terminated_ = false;

        pangolin::CreateWindowAndBind(map_viewer_name_, 1024, 768);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // depth testing to be enabled for 3D mouse handler
        glEnable(GL_DEPTH_TEST);

        // setup camera renderer
        s_cam_ = std::unique_ptr<pangolin::OpenGlRenderState>(new pangolin::OpenGlRenderState(
                pangolin::ProjectionMatrix(map_viewer_width_, map_viewer_height_, viewpoint_f_, viewpoint_f_,
                                           map_viewer_width_ / 2, map_viewer_height_ / 2, 0.1, 1e6),
                pangolin::ModelViewLookAt(viewpoint_x_, viewpoint_y_, viewpoint_z_, 0, 0, 0, 0.0, -1.0, 0.0)));

        // create map window
        pangolin::View &d_cam = pangolin::CreateDisplay()
                .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -map_viewer_width_ / map_viewer_height_)
                .SetHandler(new pangolin::Handler3D(*s_cam_));

        // create menu panel
        create_menu_panel();

        // create frame window
       // cv::namedWindow(frame_viewer_name_);

        pangolin::OpenGlMatrix gl_cam_pose_wc;
        gl_cam_pose_wc.SetIdentity();


        while (true)
        {
            // clear buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 1. draw the map window

            // get current camera pose as OpenGL matrix
            gl_cam_pose_wc = get_current_cam_pose();

            // make the rendering camera follow to the current camera
            //使渲染摄影机跟随当前摄影机
            follow_camera(gl_cam_pose_wc);

            // 设置渲染状态
            d_cam.Activate(*s_cam_);
            glClearColor(cs_.bg_.at(0), cs_.bg_.at(1), cs_.bg_.at(2), cs_.bg_.at(3));

            // draw horizontal grid  绘制水平网格
            draw_horizontal_grid();
            // draw the current camera frustum  绘制当前相机截锥
            draw_current_cam_pose(gl_cam_pose_wc);
            // draw keyframes and graphs  绘制关键帧和图形
            draw_keyframes();

            draw_points();

            // draw landmarks  绘制地标
            draw_landmarks();

            pangolin::FinishFrame();

            // 2. draw the current frame image

            //cv::imshow(frame_viewer_name_, frame_publisher_->draw_frame());

            /**
             * TODO 获取到原始图片后还需化特征
             */
            //cv::imshow(frame_viewer_name_, svo_->_l);
            //cv::waitKey(10);

            // 3. state transition

            if (*menu_reset_)
            {
                reset();
            }

            check_state_transition();

            // 4. check termination flag

            if (*menu_terminate_ || pangolin::ShouldQuit())
            {
                request_terminate();
            }

            if (terminate_is_requested())
            {
                break;
            }
        }

        /**
         *if (system_->tracker_is_paused())
        {
            system_->resume_tracker();
        }*/

        //system_->request_terminate();

        terminate();
    }

    void viewer::create_menu_panel()
    {
        pangolin::CreatePanel("menu").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(175));
        menu_follow_camera_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Follow Camera", true, true));
        menu_grid_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Show Grid", true, true));
        menu_show_keyfrms_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Show Keyframes", true, true));
        menu_show_lms_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Show Landmarks", true, true));
        menu_show_local_map_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Show Local Map", true, true));
        menu_show_graph_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Show Graph", true, true));
        menu_mapping_mode_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Mapping", mapping_mode_, true));
        menu_loop_detection_mode_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Loop Detection", loop_detection_mode_, true));
        menu_pause_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Pause", false, true));
        menu_reset_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Reset", false, false));
        menu_terminate_ = std::unique_ptr<pangolin::Var<bool>>
                (new pangolin::Var<bool>("menu.Terminate", false, false));
        menu_frm_size_ = std::unique_ptr<pangolin::Var<float>>
                (new pangolin::Var<float>("menu.Frame Size", 1.0, 1e-1, 1e1, true));
        menu_lm_size_ = std::unique_ptr<pangolin::Var<float>>
                (new pangolin::Var<float>("menu.Landmark Size", 1.0, 1e-1, 1e1, true));
    }

    void viewer::follow_camera(const pangolin::OpenGlMatrix &gl_cam_pose_wc)
    {
        if (*menu_follow_camera_ && follow_camera_)
        {
            s_cam_->Follow(gl_cam_pose_wc);
        } else if (*menu_follow_camera_ && !follow_camera_)
        {
            s_cam_->SetModelViewMatrix(
                    pangolin::ModelViewLookAt(viewpoint_x_, viewpoint_y_, viewpoint_z_, 0, 0, 0, 0.0, -1.0, 0.0));
            s_cam_->Follow(gl_cam_pose_wc);
            follow_camera_ = true;
        } else if (!*menu_follow_camera_ && follow_camera_)
        {
            follow_camera_ = false;
        }
    }

    void viewer::draw_horizontal_grid()
    {
        if (!*menu_grid_)
        {
            return;
        }

        Eigen::Matrix4f origin;
        origin << 0, 0, 1, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1;
        glPushMatrix();
        glMultTransposeMatrixf(origin.data());

        glLineWidth(1);
        glColor3fv(cs_.grid_.data());

        glBegin(GL_LINES);

        constexpr float interval_ratio = 0.1;
        constexpr float grid_min = -100.0f * interval_ratio;
        constexpr float grid_max = 100.0f * interval_ratio;

        for (int x = -10; x <= 10; x += 1)
        {
            draw_line(x * 10.0f * interval_ratio, grid_min, 0, x * 10.0f * interval_ratio, grid_max, 0);
        }
        for (int y = -10; y <= 10; y += 1)
        {
            draw_line(grid_min, y * 10.0f * interval_ratio, 0, grid_max, y * 10.0f * interval_ratio, 0);
        }

        glEnd();

        glPopMatrix();
    }

    pangolin::OpenGlMatrix viewer::get_current_cam_pose()
    {
        pangolin::OpenGlMatrix M;

        /*auto CurrentPoseTwc_ = svo_->getLastFramePose_NOLO();
        Eigen::Matrix3d Rwc = CurrentPoseTwc_.getRotation().getRotationMatrix();
        Eigen::Vector3d twc = CurrentPoseTwc_.getPosition();

        M.m[0] = Rwc(0, 0);
        M.m[1] = Rwc(1, 0);
        M.m[2] = Rwc(2, 0);
        M.m[3] = 0.0;

        M.m[4] = Rwc(0, 1);
        M.m[5] = Rwc(1, 1);
        M.m[6] = Rwc(2, 1);
        M.m[7] = 0.0;

        M.m[8] = Rwc(0, 2);
        M.m[9] = Rwc(1, 2);
        M.m[10] = Rwc(2, 2);
        M.m[11] = 0.0;

        M.m[12] = twc[0];
        M.m[13] = twc[1];
        M.m[14] = twc[2];
        M.m[15] = 1.0;
*/
        return M;
    }

    void viewer::draw_current_cam_pose(const pangolin::OpenGlMatrix &gl_cam_pose_wc)
    {
        // frustum size of the frame
        const float w = camera_size_ * *menu_frm_size_;

        glLineWidth(camera_line_width_);
        glColor3fv(cs_.curr_cam_.data());
        draw_camera(gl_cam_pose_wc, w);
    }

    void viewer::draw_points()
    {

        glPointSize(point_size_);
        glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0);

        /*const auto overlap_kfs = svo_->overlap_kfs_.at(0);

        for (size_t i = 0; i < overlap_kfs.size(); ++i)
        {
            svo::FramePtr frame = overlap_kfs[i];
            for (auto it = frame->landmark_vec_.begin();
                 it != frame->landmark_vec_.end(); ++it)
            {
                if ((*it) == NULL)
                    continue;
                Eigen::Vector3d Pw = (*it)->pos_;
                glVertex3f(Pw[0], Pw[1], Pw[2]);
            }
        }
        glEnd();

        glPointSize(point_size_);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        svo::FramePtr lastframe = svo_->getLastFrames()->at(0);
        for (auto it = lastframe->landmark_vec_.begin();
             it != lastframe->landmark_vec_.end(); ++it)
        {

            if ((*it) == NULL)
                continue;
            Eigen::Vector3d Pw = (*it)->pos_;
            glVertex3f(Pw[0], Pw[1], Pw[2]);
        }
        glEnd();*/
    }

    void viewer::draw_keyframes()
    {

        const float &w = keyfrm_size_ * *menu_frm_size_;
        const float h = w * 0.75;
        const float z = w * 0.6;

        /*CHECK_NOTNULL(svo_.get());

        static std::vector<svo::Transformation> transform_;
        if (svo_->getLastFrames() == NULL || !svo_->getLastFrames()->at(0))
        {
            // return;
        } else
        {
            svo::FramePtr lastframe = svo_->getLastFrames()->at(0);
            if (lastframe == NULL)
            {
                // return;
            } else
            {
                // save new pose
                //drawedframeID_ = lastframe->id_;
                auto CurrentPoseTwc_ = lastframe->T_f_w_.inverse();
                //xiuyong test nolo_vio
                CurrentPoseTwc_ = svo_->getLastFramePose_NOLO();
                //
                transform_.push_back(CurrentPoseTwc_);
            }
        }

        if (transform_.empty())
            return;

        glPointSize(2);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for (size_t i = 0; i < transform_.size(); i++)
        {
            auto Twc = transform_[i];
            Eigen::Vector3d pos_temp = Twc.getPosition();
            glVertex3d(pos_temp[0], pos_temp[1], pos_temp[2]);
        }
        glEnd();

*/

        // frustum size of keyframes
        //const float w = keyfrm_size_ * *menu_frm_size_;

        /**
         * TODO
         * */
        /*std::vector<data::keyframe *> keyfrms;
        map_publisher_->get_keyframes(keyfrms);

        if (*menu_show_keyfrms_)
        {
            glLineWidth(keyfrm_line_width_);
            glColor3fv(cs_.kf_line_.data());
            for (const auto keyfrm : keyfrms)
            {
                if (!keyfrm || keyfrm->will_be_erased())
                {
                    continue;
                }
                draw_camera(keyfrm->get_cam_pose_inv(), w);
            }
        }
*/
        /**
         * TODO
         * */

        /* if (*menu_show_graph_)
         {
             glLineWidth(graph_line_width_);
             glColor4fv(cs_.graph_line_.data());

             const auto draw_edge = [](const openvslam::Vec3_t &cam_center_1, const openvslam::Vec3_t &cam_center_2)
             {
                 glVertex3fv(cam_center_1.cast<float>().eval().data());
                 glVertex3fv(cam_center_2.cast<float>().eval().data());
             };

             glBegin(GL_LINES);

             for (const auto keyfrm : keyfrms)
             {
                 if (!keyfrm || keyfrm->will_be_erased())
                 {
                     continue;
                 }

                 const openvslam::Vec3_t cam_center_1 = keyfrm->get_cam_center();

                 // covisibility graph
                 const auto covisibilities = keyfrm->graph_node_->get_covisibilities_over_weight(100);
                 if (!covisibilities.empty())
                 {
                     for (const auto covisibility : covisibilities)
                     {
                         if (!covisibility || covisibility->will_be_erased())
                         {
                             continue;
                         }
                         if (covisibility->id_ < keyfrm->id_)
                         {
                             continue;
                         }
                         const openvslam::Vec3_t cam_center_2 = covisibility->get_cam_center();
                         draw_edge(cam_center_1, cam_center_2);
                     }
                 }

                 // spanning tree
                 auto spanning_parent = keyfrm->graph_node_->get_spanning_parent();
                 if (spanning_parent)
                 {
                     const openvslam::Vec3_t cam_center_2 = spanning_parent->get_cam_center();
                     draw_edge(cam_center_1, cam_center_2);
                 }

                 // loop edges
                 const auto loop_edges = keyfrm->graph_node_->get_loop_edges();
                 for (const auto loop_edge : loop_edges)
                 {
                     if (!loop_edge)
                     {
                         continue;
                     }
                     if (loop_edge->id_ < keyfrm->id_)
                     {
                         continue;
                     }
                     const openvslam::Vec3_t cam_center_2 = loop_edge->get_cam_center();
                     draw_edge(cam_center_1, cam_center_2);
                 }
             }

             glEnd();
         }
    */
    }


    void viewer::draw_landmarks()
    {
        if (!*menu_show_lms_)
        {
            return;
        }

        /**
         * TODO
         * */
        /*std::vector<data::landmark *> landmarks;
        std::set<data::landmark *> local_landmarks;

        map_publisher_->get_landmarks(landmarks, local_landmarks);

        if (landmarks.empty())
        {
            return;
        }*/

        glPointSize(point_size_ * *menu_lm_size_);
        glColor3fv(cs_.lm_.data());

        glBegin(GL_POINTS);


        /**
         * TODO
         * */
        /*    for (const auto lm : landmarks)
            {
                if (!lm || lm->will_be_erased())
                {
                    continue;
                }
                if (*menu_show_local_map_ && local_landmarks.count(lm))
                {
                    continue;
                }
                const Vec3_t pos_w = lm->get_pos_in_world();
                glVertex3fv(pos_w.cast<float>().eval().data());
            }
    */
        glEnd();

        if (!*menu_show_local_map_)
        {
            return;
        }

        glPointSize(point_size_ * *menu_lm_size_);
        glColor3fv(cs_.local_lm_.data());

        glBegin(GL_POINTS);

        /**
         * TODO
         * */
        /*for (const auto local_lm : local_landmarks)
        {
            if (local_lm->will_be_erased())
            {
                continue;
            }
            const Vec3_t pos_w = local_lm->get_pos_in_world();
            glVertex3fv(pos_w.cast<float>().eval().data());
        }*/

        glEnd();
    }

    void viewer::draw_camera(const pangolin::OpenGlMatrix &gl_cam_pose_wc, const float width) const
    {
        glPushMatrix();
#ifdef HAVE_GLES
        glMultMatrixf(cam_pose_wc.m);
#else
        glMultMatrixd(gl_cam_pose_wc.m);
#endif

        glBegin(GL_LINES);
        draw_frustum(width);
        glEnd();

        glPopMatrix();
    }

    void viewer::draw_camera(const Mat44_t &cam_pose_wc, const float width) const
    {
        glPushMatrix();
        glMultMatrixf(cam_pose_wc.transpose().cast<float>().eval().data());

        glBegin(GL_LINES);
        draw_frustum(width);
        glEnd();

        glPopMatrix();
    }

    void viewer::draw_frustum(const float w) const
    {
        const float h = w * 0.75f;
        const float z = w * 0.6f;
        // 四角錐の斜辺
        draw_line(0.0f, 0.0f, 0.0f, w, h, z);
        draw_line(0.0f, 0.0f, 0.0f, w, -h, z);
        draw_line(0.0f, 0.0f, 0.0f, -w, -h, z);
        draw_line(0.0f, 0.0f, 0.0f, -w, h, z);
        // 四角錐の底辺
        draw_line(w, h, z, w, -h, z);
        draw_line(-w, h, z, -w, -h, z);
        draw_line(-w, h, z, w, h, z);
        draw_line(-w, -h, z, w, -h, z);
    }

    void viewer::reset()
    {
        // reset menu checks
        *menu_follow_camera_ = true;
        *menu_show_keyfrms_ = true;
        *menu_show_lms_ = true;
        *menu_show_local_map_ = true;
        *menu_show_graph_ = true;
        *menu_mapping_mode_ = mapping_mode_;
        *menu_loop_detection_mode_ = loop_detection_mode_;

        // reset menu button
        *menu_reset_ = false;
        *menu_terminate_ = false;

        // reset mapping mode
        if (mapping_mode_)
        {
            // system_->enable_mapping_module();
        } else
        {
            //system_->disable_mapping_module();
        }

        // reset loop detector
        if (loop_detection_mode_)
        {
            // system_->enable_loop_detector();
        } else
        {
            //system_->disable_loop_detector();
        }

        // reset internal state
        follow_camera_ = true;

        // execute reset
        //system_->request_reset();
    }

    void viewer::check_state_transition()
    {
        // pause of tracker
        /*if (*menu_pause_ && !system_->tracker_is_paused())
        {
            system_->pause_tracker();
        } else if (!*menu_pause_ && system_->tracker_is_paused())
        {
            system_->resume_tracker();
        }*/

        // mapping module
        if (*menu_mapping_mode_ && !mapping_mode_)
        {
            //system_->enable_mapping_module();
            mapping_mode_ = true;
        } else if (!*menu_mapping_mode_ && mapping_mode_)
        {
            // system_->disable_mapping_module();
            mapping_mode_ = false;
        }

        // loop detector
        if (*menu_loop_detection_mode_ && !loop_detection_mode_)
        {
            // system_->enable_loop_detector();
            loop_detection_mode_ = true;
        } else if (!*menu_loop_detection_mode_ && loop_detection_mode_)
        {
            // system_->disable_loop_detector();
            loop_detection_mode_ = false;
        }
    }

    void viewer::request_terminate()
    {
        std::lock_guard<std::mutex> lock(mtx_terminate_);
        terminate_is_requested_ = true;
    }

    bool viewer::is_terminated()
    {
        std::lock_guard<std::mutex> lock(mtx_terminate_);
        return is_terminated_;
    }

    bool viewer::terminate_is_requested()
    {
        std::lock_guard<std::mutex> lock(mtx_terminate_);
        return terminate_is_requested_;
    }

    void viewer::terminate()
    {
        std::lock_guard<std::mutex> lock(mtx_terminate_);
        is_terminated_ = true;
    }


    void viewer::RunData(std::size_t protocol, const char *data, std::size_t size)
    {

        (void) data;

        std::cout << "protocol:" << protocol << ",size:" << size << std::endl;


        //std::lock_guard<std::mutex> lock(_dataMutex);


        switch (protocol)
        {
            case VIEWER_IMAGE:
            {
                auto buffer = new char(size);

                memcpy(buffer, data, size);

                auto img = cv::Mat(400, 1280, CV_8UC1, buffer);

                delete buffer;

                {
                    std::lock_guard<std::mutex> lock(_dataMutex);

                    _dataImg = std::move(img);
                }

                break;
            }
            case VIEWER_KEY_POINT:
            {
                cv::Mat img;

                _dataImg.copyTo(_dataKeyImg);

                /**
                 * key point
                 * */
                {

                }

                {
                    std::lock_guard<std::mutex> lock(_dataMutex);

                    _dataKeyImg = std::move(img);
                }

                break;
            }
            case VIEWER_TRAJECTORY:
            {

                {
                    std::lock_guard<std::mutex> lock(_dataMutex);

                    //_trajectory.push_back();
                }


                break;
            }
            case VIEWER_ALL_POINT_CLOUD:
            {
                {
                    std::lock_guard<std::mutex> lock(_dataMutex);

                    //_allPointCloud.push_back();
                }
                break;
            }
            case VIEWER_CURRENT_POINT_CLOUD:
            {
                {
                    std::lock_guard<std::mutex> lock(_dataMutex);

                    //_currentPointCloud.push_back();
                }
                break;
            }
            default:
            {
                
            }
        }
    }
} // namespace pangolin_viewer
