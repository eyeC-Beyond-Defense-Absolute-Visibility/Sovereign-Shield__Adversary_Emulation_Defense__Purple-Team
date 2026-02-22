/* * Definition of the Orchestrator engine interface.
 * This class handles configuration loading, health monitoring, 
 * and infrastructure deployment/isolation.
 */

#ifndef ORCHESTRATOR_HPP
#define ORCHESTRATOR_HPP

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Orchestrator {
public:
    // Default constructor
    Orchestrator();

    /**
     * @brief Loads the system configuration from a JSON file.
     * @param configPath Path to the config.json file.
     * @return true if loading succeeded, false otherwise.
     */
    bool loadConfig(const std::string& configPath);

    /**
     * @brief Performs a health check on the monitored infrastructure.
     */
    void runHealthCheck();

    /**
     * @brief Initiates the deployment of the Sovereign-Shield security layers.
     */
    void deployShield();

    /**
     * @brief Triggers emergency isolation for a specific node.
     * @param nodeName The identifier or IP address of the target node.
     */
    void triggerIsolation(const std::string& nodeName);

private:
    // Stores the parsed configuration data
    json config;

    // Internal state to track if the engine is ready
    bool isConfigLoaded = false;

    /**
     * @brief Internal helper to run system-level shell commands.
     * @param cmd The shell command to be executed.
     */
    void executeCommand(const std::string& cmd);
};

#endif