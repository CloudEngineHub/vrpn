/** @file
	@brief Header

	@date 2014

	@author
	Kevin M. Godby
	<kevin@godby.org>
*/

#ifndef VRPN_TRACKER_OCULUS_RIFT_H_
#define VRPN_TRACKER_OCULUS_RIFT_H_

// Internal Includes
#include "quat.h"                       // for q_vec_type
#include "vrpn_Analog.h"                // for vrpn_Analog
#include "vrpn_Tracker.h"               // for vrpn_Tracker

// Library/third-party includes
#include <OVR.h>

// Standard includes
#include <string>

#ifdef VRPN_USE_OVR

/** @brief Device supporting the Oculus Rift DK1 and DK2.
 *
 * The Oculus Rift hardware contains a number of MEMS sensors including a
 * gyroscope, acceleromter, and magnetometer. Starting with DK2, there is also
 * an external camera to track the HMD position.
 */
class VRPN_API vrpn_Tracker_OculusRift : public vrpn_Analog, public vrpn_Tracker
{
public:
    vrpn_Tracker_OculusRift(const char* name, vrpn_Connection* conn, int hmd_index = 0, const char* hmd_type = "Debug");
    virtual ~vrpn_Tracker_OculusRift();

    virtual void mainloop();

private:
    enum {
        ANALOG_CHANNELS = 10, // accelerometer[3], gyro[3], magnetometer[3], temperature
        POSE_CHANNELS = 3     // head, camera, leveled camera
    };

    void _get_tracking_state();

    /**
     * Returns the readable name of the HMD type.
     *
     * @param hmd_type HMD type from ovrHmdType enum.
     *
     * @returns String of HMD type name.
     */
    std::string _get_hmd_type_name(ovrHmdType hmd_type) const;

    /**
     * Returns the enum value of the HMD type.
     *
     * @param hmd_type The type of HMD. Acceptable values are: DK1, DK2, and
     * Debug.
     *
     * @return The enum valuie of the hmd_type.
     */
    ovrHmdType _get_hmd_type(std::string hmd_type) const;

    ovrHmd _hmd;                        //< HMD device handle
    ovrHmdType _hmdType;                //< requested HMD type


    q_xyz_quat_type _headPose;          //< head pose
    q_xyz_quat_type _cameraPose;        //< camera pose
    q_xyz_quat_type _leveledCameraPose; //< leveled camera pose

    q_vec_type _accelerometer;          //< acceleration reading in m/s^2
    q_vec_type _gyroscope;              //< rotation rate in rad/s
    q_vec_type _magnetometer;           //< magnetic field in Gauss
    float _temperature;                 //< temperature in degrees Celsius
};

#else
class VRPN_API vrpn_Tracker_OculusRift;
#endif // VRPN_USE_OVR

#endif // VRPN_TRACKER_OCULUS_RIFT_H_

