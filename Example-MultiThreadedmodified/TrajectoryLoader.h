#ifndef TRAJECTORY_LOADER_H
#define TRAJECTORY_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct JointTrajectory {
    double angle;
    double velocity;
    double acceleration;
};

struct FullBodyTrajectoryPoint {
    double time;  // Time from CSV (e.g., Gait Cycle %)
    JointTrajectory rightHip;
    JointTrajectory rightKnee;
    JointTrajectory rightAnkle;
    JointTrajectory leftHip;
    JointTrajectory leftKnee;
    JointTrajectory leftAnkle;
};

class TrajectoryLoader {
public:
    static std::vector<FullBodyTrajectoryPoint> LoadFromCSV(const std::string& filePath) {
        std::vector<FullBodyTrajectoryPoint> points;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file at " << filePath << std::endl;
            return points;
        }

        std::string line;

        // Skip header line
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue; // Skip empty lines

            std::stringstream ss(line);
            std::string item;
            FullBodyTrajectoryPoint point;

            try {
                // Read and convert all values in order
                std::getline(ss, item, ','); point.time = std::stod(item);

                std::getline(ss, item, ','); point.rightHip.angle = std::stod(item);
                std::getline(ss, item, ','); point.rightHip.velocity = std::stod(item);
                std::getline(ss, item, ','); point.rightHip.acceleration = std::stod(item);

                std::getline(ss, item, ','); point.rightKnee.angle = std::stod(item);
                std::getline(ss, item, ','); point.rightKnee.velocity = std::stod(item);
                std::getline(ss, item, ','); point.rightKnee.acceleration = std::stod(item);

                std::getline(ss, item, ','); point.rightAnkle.angle = std::stod(item);
                std::getline(ss, item, ','); point.rightAnkle.velocity = std::stod(item);
                std::getline(ss, item, ','); point.rightAnkle.acceleration = std::stod(item);

                std::getline(ss, item, ','); point.leftHip.angle = std::stod(item);
                std::getline(ss, item, ','); point.leftHip.velocity = std::stod(item);
                std::getline(ss, item, ','); point.leftHip.acceleration = std::stod(item);

                std::getline(ss, item, ','); point.leftKnee.angle = std::stod(item);
                std::getline(ss, item, ','); point.leftKnee.velocity = std::stod(item);
                std::getline(ss, item, ','); point.leftKnee.acceleration = std::stod(item);

                std::getline(ss, item, ','); point.leftAnkle.angle = std::stod(item);
                std::getline(ss, item, ','); point.leftAnkle.velocity = std::stod(item);
                std::getline(ss, item, ','); point.leftAnkle.acceleration = std::stod(item);

                points.push_back(point);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << "\nReason: " << e.what() << std::endl;
                continue;
            }
        }

        return points;
    }
};

#endif // TRAJECTORY_LOADER_H
