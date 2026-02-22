# 🛡️ Sovereign Shield
![K3s](https://img.shields.io/badge/Kubernetes-K3s-326ce5?logo=kubernetes&logoColor=white)
![Cilium](https://img.shields.io/badge/Cilium-eBPF-ffcc00?logo=cilium&logoColor=black)
![eBPF](https://img.shields.io/badge/Linux-eBPF-000000?logo=linux&logoColor=white)
![Security](https://img.shields.io/badge/Security-Zero--Trust-red)

---

# 🛡️ Sovereign-Shield v2: Complexify Not Crazyfy

**High-Performance Purple Team Orchestration & Multi-Node Defense**

Sovereign-Shield v2 is a unified security framework designed to bridge the gap between offensive emulation and automated, forensically-sound defense. Built on the "Genesis" foundation, v2 introduces a heterogeneous multi-node environment, shifting from simple scripts to a professional Security Control Plane.

---

## 🎯 Project Goals

* **Multi-OS Orchestration:** Manage defense across Debian, AlmaLinux, and Windows Server 2019/11.
* **eBPF-Powered Observability:** Deep kernel-level traffic analysis via Cilium & Hubble.
* **MITRE ATT&CK Alignment:** Automated adversary emulation (Lateral Movement, Exfiltration).
* **Forensic Maturity:** Evidence-first incident response (NIST SP 800-61 compliant).

---

## 🧱 Architecture (The eyeC Lab)

The environment mimics a realistic corporate network with segmented LAN/WAN zones.
```
               🌍 SIMULATED WAN
          [ Kali Linux (Red Team) ]
                     │
          (Attacks / Scans / Exploits)
                     ▼
┌─────────────────────────────────────────────┐
│       🧱 CONTROL ZONE / SHIELD NODE         │
│     Debian 12 – C++ Orchestration Engine    │
└──────────┬──────────────────────┬───────────┘
           │                      │
           ▼                      ▼
┌──────────────────────┐  ┌────────────────────────┐
│  🛡️ PROTECTED LAN    │  │   🏢 WINDOWS DOMAIN    │
│ [Ubuntu] [AlmaLinux] │  │ [Win Server] [Win 11]  │
│ [Metasploitable 3]   │  │ (Forensic IR Enabled)  │
└──────────────────────┘  └────────────────────────┘
```

---

## 🛠️ Why C++ for Purple Teaming?

**A strategic choice for the eyeC initiative**

1. **Deterministic Performance:** In active defense, millisecond delays in eBPF processing can be the difference between containment and catastrophe.
2. **Binary Integrity:** Compiled C++ binaries provide a smaller attack surface and higher tamper resistance compared to interpreted scripts.
3. **Memory Mastery:** Demonstrates deep understanding of system-level interactions—crucial for analyzing memory-resident malware.

---

## 🔍 Forensic Strategy & Operational Maturity

We follow the **NIST SP 800-61** standard for incident handling. Sovereign-Shield does not just "kill" a threat; it preserves the digital crime scene.

* **Live Forensics:** Automatically captures volatile data (active network sockets, RAM process trees) before node isolation.
* **Cross-Platform IR:** Unified C++ logic that understands the difference between `iptables` (Linux) and `Netsh` (Windows).
* **Audit Trail:** All evidence is fetched back to the Control Plane for root-cause analysis.

---

## 🚀 Getting Started

### 1. Prerequisites

* **Hypervisor:** VMware or Proxmox.
* **Tools:** `cmake`, `g++`, `ansible`, `cilium-cli`.

### 2. Installation
```bash
<<<<<<< HEAD
git clone https://github.com/OBadolo/Sovereign-Shield.git
=======
git clone https://github.com/your-username/Sovereign-Shield.git
>>>>>>> main
cd Sovereign-Shield
chmod +x setup.sh
./setup.sh
```

### 3. Build & Run
```bash
./build.sh
./build/bin/SovereignShield
```

---

## 🧪 Roadmap: Implementation Phases

* [x] Phase 1: Network Segmentation & Multi-OS Deployment.
* [x] Phase 2: Shield Deployment (K3s + Cilium eBPF).
* [x] Phase 3: Active Defense (L7 Identity-Aware Policies).
<<<<<<< HEAD
* [x] Phase 4: Advanced Emulation (C2 Channel simulation).
* [x] Phase 5: Governance & Automated Reporting.
=======
* [ ] Phase 4: Advanced Emulation (C2 Channel simulation).
* [ ] Phase 5: Governance & Automated Reporting.
>>>>>>> main

---

## 👁️ About eyeC

**eyeC**(ybersecurity) ~ (... I See) is a personal lab initiative by O'djuma Badolo. It focuses on making the invisible visible through eBPF observability and building robust, automated foundations for modern DevSecOps.

---

## 👤 Author

**O'djuma Badolo**  
Web Developer | Cybersecurity graduate | DevSecOps Enthusiast  
> *"Build the foundation. Then earn the complexity."*
