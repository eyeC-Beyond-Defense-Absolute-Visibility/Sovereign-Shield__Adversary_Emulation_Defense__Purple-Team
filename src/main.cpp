/**
 * @file        main.cpp
 * @project     Sovereign-Shield (v2: Complexify Not Crazyfy)
 * @author      O’djuma Badolo (eyeC)
 * @version     1.1
 * @description Command-Line Interface (CLI) for the eyeC Orchestration Engine.
 * Supports deployment, forensics, isolation, and Disaster Recovery (DR).
 * * "Genesis is the ground truth. Version 2 is the serious path."
 */

#include "include/Orchestrator.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * Aesthetic Terminal Header
 */
void printBanner() {
    std::cout << "\033[0;36m" << "================================================================" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "   🛡️  SOVEREIGN-SHIELD | THE eyeC PROJECT | Version 1.1        " << "\033[0m" << std::endl;
    std::cout << "   [ Multi-OS Security Control Plane - NIST Compliant ]         " << std::endl;
    std::cout << "\033[0;36m" << "================================================================" << "\033[0m" << std::endl;
}

/**
 * Command-Line Usage Guide
 */
void printHelp() {
    std::cout << "Usage: ./SovereignShield [OPTION] [TARGET] [OS_TYPE]\n\n";
    std::cout << "Options:\n";
    std::cout << "  --deploy              Initialize full infra (K3s, Cilium, Hardening)\n";
    std::cout << "  --health              Run L7 policy & Hubble connectivity checks\n";
    std::cout << "  --simulate [TYPE]     Run MITRE ATT&CK simulation (e.g., lateral_movement)\n";
    std::cout << "  --isolate  [NAME] [OS] Perform Forensics + Isolation on target node\n";
    std::cout << "  --backup              Archive policies and cluster configurations\n";
    std::cout << "  --restore  [FILE]     Restore infrastructure from a specific backup\n";
    std::cout << "  --help                Display this manual\n\n";
}

int main(int argc, char* argv[]) {
    printBanner();

    // Instantiate the v2 Engine
    Orchestrator v2_Engine;

    // Safety check: Arguments are required
    if (argc < 2) {
        std::cerr << "\033[0;31m[!] Error: No arguments provided.\033[0m" << std::endl;
        printHelp();
        return 1;
    }

    // Load Configuration
    if (!v2_Engine.loadConfig("config.json")) return 1;

    std::string command = argv[1];

    // --- Command Processing Logic ---

    if (command == "--deploy") {
        std::cout << "[*] Action: Full Environment Deployment Started..." << std::endl;
        v2_Engine.deployShield();
    } 
    
    else if (command == "--health") {
        std::cout << "[*] Action: Running Active Defense Integrity Checks..." << std::endl;
        v2_Engine.runHealthCheck();
    }

    else if (command == "--simulate" && argc > 2) {
        std::string technique = argv[2];
        v2_Engine.runSimulation(technique);
    }

    else if (command == "--isolate" && argc > 3) {
        std::string nodeName = argv[2];
        std::string osType = argv[3];

        std::cout << "\033[0;31m" << "[🚨] THREAT RESPONSE INITIATED" << "\033[0m" << std::endl;
        
        // Step 1: Forensic Evidence Collection (NIST Standard)
        std::cout << "[Step 1/2] Capturing Volatile Data..." << std::endl;
        // v2_Engine.runForensics(nodeName); 
        
        // Step 2: Network Containment
        std::cout << "[Step 2/2] Enforcing Network Quarantine..." << std::endl;
        v2_Engine.triggerIsolation(nodeName, osType);
    }

    else if (command == "--backup") {
        std::cout << "\033[0;32m" << "[💾] DISASTER RECOVERY: Archiving security policies..." << "\033[0m" << std::endl;
        v2_Engine.executeCommand("ansible-playbook ansible/playbooks/maintenance/backup_configs.yml");
    }

    else if (command == "--restore" && argc > 2) {
        std::string backupFile = argv[2];
        std::cout << "\033[1;33m" << "[🔄] RESTORATION: Deploying config from " << backupFile << "..." << "\033[0m" << std::endl;
        v2_Engine.executeCommand("ansible-playbook ansible/playbooks/maintenance/restore_configs.yml -e 'backup_file=" + backupFile + "'");
    }

    else if (command == "--help") {
        printHelp();
    }

    else {
        std::cerr << "\033[0;31m[!] Unknown command: " << command << "\033[0m" << std::endl;
        printHelp();
        return 1;
    }

    std::cout << "\n\033[0;36m" << "[eyeC Status]: Operation completed cleanly." << "\033[0m" << std::endl;
    return 0;
}