#include "camera.h"

void Camera::freelook() { // not to be confused with look_at. we only look what is in front of the camera.
    view_matrix = glm::lookAt(position, position + front, up);
    
}
