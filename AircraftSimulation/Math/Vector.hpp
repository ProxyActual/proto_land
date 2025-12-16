#pragma once
#include <cmath>

class vector_3d{
    public:
        float x;
        float y;
        float z;

        vector_3d(): x(0), y(0), z(0) {}

        vector_3d(float x, float y, float z): x(x), y(y), z(z) {}

        vector_3d operator+(const vector_3d& other) const {
            return vector_3d(x + other.x, y + other.y, z + other.z);
        }

        vector_3d operator-(const vector_3d& other) const {
            return vector_3d(x - other.x, y - other.y, z - other.z);
        }

        vector_3d operator*(float scalar) const {
            return vector_3d(x * scalar, y * scalar, z * scalar);
        }

        vector_3d operator/(float scalar) const {
            return vector_3d(x / scalar, y / scalar, z / scalar);
        }

        vector_3d convertToWorld(const vector_3d& localAttitude) const {
            float cphi = cos(localAttitude.y * M_PI / 180.0f);
            float sphi = sin(localAttitude.y * M_PI / 180.0f);
            float ctheta = cos(localAttitude.x * M_PI / 180.0f);
            float stheta = sin(localAttitude.x * M_PI / 180.0f);
            float cpsi = cos(localAttitude.z * M_PI / 180.0f);
            float spsi = sin(localAttitude.z * M_PI / 180.0f);

            float worldX = x * (ctheta * cpsi) + y * (sphi * stheta * cpsi - cphi * spsi) + z * (cphi * stheta * cpsi + sphi * spsi);
            float worldY = x * (ctheta * spsi) + y * (sphi * stheta * spsi + cphi * cpsi) + z * (cphi * stheta * spsi - sphi * cpsi);
            float worldZ = x * (-stheta) + y * (sphi * ctheta) + z * (cphi * ctheta);

            return vector_3d(worldX, worldY, worldZ);
        }

        float magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }
};