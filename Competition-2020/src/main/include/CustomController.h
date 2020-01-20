#include <frc/WPILib.h>

using namespace frc;

/**
 * Handle input from Xbox 360 or Xbox One controllers connected to the Driver
 * Station.
 *
 * This class handles Xbox input that comes from the Driver Station. Each time a
 * value is requested the most recent value is returned. There is a single class
 * instance for each controller and the mapping of ports to hardware buttons
 * depends on the code in the Driver Station.
 * 
 * This class is a modified version of XboxController.
 */
class CustomController : public XboxController {
  public:

    /**
     * Construct an instance of our custom Xbox controller.
     *
     * The controller index is the USB port on the Driver Station.
     *
     * @param port The port on the Driver Station that the controller is plugged
     *             into (0-5).
     */
    explicit CustomController(int port);
    
    /**
     * Set the scale of the controller. The scale cannot be negative.
     * 
     * @param scale The scale to set the controller to.
     */
    void set_scale(float scale);

    /**
     * Get the current scaling of the controller.
     * 
     * @return The current scaling of the controller.
     */
    float get_scale();

    /**
     * Sets a square scaling.
     * 
     * The controller is 0 until a certain percent, then 1 at or after the percent.
     * 
     * For example, a square curve at 50 percent would set the controller to 0 until it is moved to the halfway point.
     * 
     * @param percent The percent (0-100) that the controller is set to 0.
     */
    void square_scale(float percent);

    /**
     * Returns the percent that the square scale is at. If a square scale is not used, it returns -1.
     * 
     * @return The square scale percent, or -1 if not applicable.
     */
    float get_square();
    
    /**
     * Get the value of the axis times the current scale. A deadzone of 0.1 is implemented.
     *
     * @param axis The axis to read, starting at 0.
     * @return The value of the axis between -1 and 1.
     */
    double GetRawAxis(int axis);
    
  private:
    float scale;
    bool square;
};