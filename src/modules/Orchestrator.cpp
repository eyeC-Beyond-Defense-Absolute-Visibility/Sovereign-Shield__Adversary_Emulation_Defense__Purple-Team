/**
 * Orchestrator v2 - Multi-OS Support
 * Handles complex infrastructure including Windows and Linux nodes.
 * The C++ logic now distinguishes between Windows and Linux for isolation, as the commands (IPTables vs. PowerShell/Firewall) differ.
 */

#include "Orchestrator.hpp"
#include <iostream>

// ... loadConfig remains similar but now handles the v2 structure ...

/**
 * Enhanced Isolation: Detects OS type and runs targeted playbooks.
 */
void Orchestrator::triggerIsolation(const std::string& nodeName, const std::string& osType) {
    if (!isConfigLoaded) return;

    std::cout << "[🚨] V2 ALERT: Isolating " << nodeName << " (" << osType << ")" << std::endl;

    // We can pass the OS type as an extra variable to Ansible
    // so the playbook knows whether to use IPTables or Windows Firewall
    std::string cmd = "ansible-playbook " + config["ansible_config"]["playbooks"]["isolate"].get<std::string>() 
                    + " -e 'target=" + nodeName 
                    + " os_family=" + osType + "'";
    
    executeCommand(cmd);
}

/**
 * Simulation Runner: Executes MITRE-mapped attack scenarios.
 */
void Orchestrator::runSimulation(const std::string& technique) {
    std::cout << "[🧪] Simulation Started: MITRE ATT&CK " << technique << std::endl;
    // Example: lateral_movement
    std::string path = "ansible/simulations/" + technique + "/main.yml";
    executeCommand("ansible-playbook " + path);
}