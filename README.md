# 🛡️ SOVEREIGN SHIELD

# 🌱 **Version 1.0 · Genesis of Sovereign Shield

![VMware](https://img.shields.io/badge/VMware-Virtualization-607078?logo=vmware\&logoColor=white)
![K3s](https://img.shields.io/badge/Kubernetes-K3s-326ce5?logo=kubernetes\&logoColor=white)
![Cilium](https://img.shields.io/badge/Cilium-eBPF-ffcc00?logo=cilium\&logoColor=black)
![eBPF](https://img.shields.io/badge/Linux-eBPF-000000?logo=linux\&logoColor=white)
![Security](https://img.shields.io/badge/Security-Zero--Trust-red)



---

## *Genesis: Overview*

> **Genesis** is an intentionally minimal and stable foundation; a core infrastructure and birth of an eBPF-based defensive lab
> It is a **controlled environment** designed to prove one thing well:
> **kernel-level network enforcement using eBPF in Kubernetes**.
**Sovereign Shield – Genesis** is the first iteration of a broader Purple Team security project.

This version focuses exclusively on:

* building a **clean Kubernetes baseline** (K3s)
* replacing default networking with **eBPF-powered enforcement** (Cilium)
* validating **Zero Trust principles** through observable, reproducible behavior

No automation sprawl. No artificial complexity.
Just a **solid security core**.

---

## 🎯 Genesis Objectives

* Deploy a **K3s cluster without default networking**
* Enforce network controls using **Cilium (eBPF)**
* Enable **real-time observability** with Hubble
* Demonstrate **L3 / L4 / L7 policy enforcement**
* Provide visual, undeniable proof of traffic control

---

## 🧱 Genesis Lab Architecture

```
ansible/
├── scripts/              # Ansible playbooks & bash scripts
│   ├── deploy_shield.yml
│   └── enable_hubble.yml
├── policies/             # Cilium security policies (.yaml)
│   └── shield-policy.yaml
└── inventory.ini         # Target machines inventory
```

```
[ Test Pod ] ──▶ [ K3s + Cilium (eBPF) ] ──▶ [ External / Internal Targets ]
                        │
                     [ Hubble ]
```

**Genesis Key characteristics**:

* Single-node cluster
* Explicit deny-by-default posture
* Visibility-first security model

---

## 🛠️ Genesis core Components

| Component  | Purpose                              |
| ---------- | ------------------------------------ |
| **VMware** | Virtualized lab environment          |
| **K3s**    | Lightweight Kubernetes control plane |
| **Cilium** | eBPF-based networking & security     |
| **Hubble** | Real-time network observability      |
| **eBPF**   | Kernel-level enforcement engine      |

---

## 🛡️ Genesis Security Model

The 1.0 enforces a **Zero Trust baseline**:

* ❌ No implicit allow rules
* ✅ Explicit traffic authorization only
* 👁️ Every decision is observable

### Example policy behavior

| Source | Destination     | Method | Result           |
| ------ | --------------- | ------ | ---------------- |
| Pod    | Internet        | HTTP   | **DROPPED** ❌    |
| Pod    | Internal Target | GET    | **ALLOWED** ✅    |
| Pod    | Internal Target | POST   | **REJECTED** 🛡️ |

---

## 🔍 Genesis observability (Hubble)

Genesis prioritizes **seeing before scaling**.

Hubble provides:

* real-time flow visibility
* dropped packet inspection
* L7 (HTTP) decision tracing

This ensures that **every security decision is explainable**.

---

## 📸 Documentation & description (des_CRx(ip/'een')--tion)
### Documentation
**🧪 Key Commands — Version 1 (Genesis)**

> This section documents **exactly what is executed** and **why**.
> Goal: reproducibility and understanding, not automation sprawl.

### 1️⃣ K3s installation (no default networking)

```bash
curl -sfL https://get.k3s.io | \
INSTALL_K3S_EXEC="--flannel-backend=none --disable-network-policy --disable traefik" \
sh -
```

**What this does:**

* installs a minimal K3s cluster
* disables Flannel (default CNI)
* prevents any implicit network policy
* prepares the cluster for Cilium (eBPF)

---

### 2️⃣ Kubernetes cluster access

```bash
export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
```

**Purpose:**

* allows `kubectl` and `cilium` to communicate with the Kubernetes API

---

### 3️⃣ Cilium installation (eBPF)

```bash
cilium install \
  --set k8sServiceHost=127.0.0.1 \
  --set k8sServicePort=6443
```

**Purpose:**

* fully replaces Kubernetes networking
* injects eBPF programs into the Linux kernel
* enables L3 / L4 / L7 enforcement

---

### 4️⃣ Observability activation (Hubble)

```bash
cilium hubble enable --ui
```

**Purpose:**

* enables network telemetry
* provides real-time visibility into eBPF decisions

---

### 5️⃣ Test pod deployment

```bash
kubectl run tracer \
  --image=curlimages/curl \
  -- sh -c "while true; do curl -sL google.com > /dev/null; sleep 2; done"
```

**Purpose:**

* generates controlled outbound traffic
* establishes a baseline before and after policy enforcement

---

### 6️⃣ Cilium policy application

```bash
kubectl apply -f policies/l7/http-restrict.yaml
```

**Purpose:**

* enforces a Zero Trust model
* explicitly allows known-good traffic
* blocks everything else by default

---

### 7️⃣ Flow visualization

```bash
cilium hubble ui
```

**Purpose:**

* visually inspect:

  * allowed flows
  * dropped packets
  * L7 decisions

---


### Description


This section include visual screenshots as description about:

* default-allow behavior **before** enforcement
* traffic blocked **after** policy application
* L7 method-level filtering

> 📌 **VMware Workstation / ESXi Topology**  
<img width="3839" height="2293" alt="Screenshot of my VMware with used machines" src="https://github.com/user-attachments/assets/ee6b86a3-2c61-42f6-8853-a944fda849ec" />

### 🔓 Before — Default Kubernetes Behavior
Traffic flows freely without restrictions.
<img src="https://github.com/user-attachments/assets/19b1428e-5f39-4f69-9275-6beebf011506" />

###🔒 After — Zero-Trust eBPF Shield Enabled
Unauthorized egress traffic is blocked.
<img src="https://github.com/user-attachments/assets/a354abd1-cf00-4424-bd52-59fe0560d2bc" />

### 🔍 Layer 7 (L7) Inspection — HTTP Filtering
GET requests allowed, POST requests blocked (eBPF proxy).
<img src="https://github.com/user-attachments/assets/8c0b8c4e-7963-4085-9fdb-172d39d1f0ff" />

### 🧠 Advanced L7 Enforcement
Selective HTTP method filtering prevents data exfiltration.
<img src="https://github.com/user-attachments/assets/05d433a2-06ca-4bad-a697-3ff814dc857d" />

> Screenshots are intentionally limited in this version.
> Genesis proves *capability*, not *coverage*.
> 1.0 Genesis is the **reference baseline** upon which everything else will grow.


## 🔜 What comes next?

### Version 1.1 — **Complexify · Not Crazyfy**

The next iteration introduces:

* multi-node environments
* explicit threat actors
* Red / Blue / Purple workflows
* automated containment
* MITRE ATT&CK alignment

Genesis is the **ground truth**.
Version 2 is where things become serious.

# End of Version 1.0: GENESIS
---

## 👤 Author

**O’djuma Badolo**
Cybersecurity • Cloud • DevSecOps
> *"Build the foundation. Then earn the complexity."*

---
 
 
 # 🛡️ Version 1.1 · Complexify Not Crazyfy Sovereign-Shield 🤪

> Version 1.1 (Complexify Not Crazyfy) of Sovereign Shield builds on the Genesis version (1.0) by extending a segmented LAN/WAN environment with additional hosts and services to continuously test, detect, and contain network and application attacks.
The lab combines eBPF-based security, Kubernetes (K3s), Cilium, Hubble, and Ansible to enable iterative Red Team simulations and automated Blue Team response.

---

## 🎯 Project Goals

- Design a **segmented LAN/WAN network architecture**
- Deploy a **secure Kubernetes cluster without the default CNI**
- Enforce **L3/L4/L7 security policies using eBPF**
- Observe and analyze network flows in real time
- Simulate attacks mapped to **MITRE ATT&CK**
- Automate **incident response and quarantine**
- Establish a continuous **Purple Team feedback loop**

---

## 🧱 Architecture

### Minimized Diagram
```
[ Kali (Red) ] ──┐
│ ┌──────────────┐
[ LAN Segment ]──┼──────▶ │ K3s Cluster │──▶ Application Services
│ │ + Cilium │
[ WAN Segment ]──┘ │ + Hubble │
└──────────────┘
│
[ Ansible IR ]
```

### Detailed Diagram
```
                               🌍 SIMULATED INTERNET / WAN
                               Network: XX.X.X.X/XX
┌──────────────────────────────────────────────────────────────────────┐
│                                                                      │
│   ┌──────────────────────────────┐                                   │
│   │  Kali Linux (Red Team)        │                                   │
│   │------------------------------│                                   │
│   │  IP        : XX.X.X.X        │                                   │
│   │  Interface : eth0             │                                   │
│   │                              │                                   │
│   │  Capabilities:               │                                   │
│   │   • Reconnaissance (Nmap)     │                                   │
│   │   • Exploitation (Metasploit) │                                   │
│   │   • Brute Force               │                                   │
│   │                              │                                   │
│   └───────────────┬──────────────┘                                   │
│                   │                                                     
│        Attacks / Scans / Exploits                                     
│                   │                                                     
└───────────────────┼──────────────────────────────────────────────────┘
                    │
                    │  WAN ↔ LAN Boundary
                    │
┌───────────────────▼──────────────────────────────────────────────────┐
│                    🧱 CONTROL ZONE / SHIELD NODE                      │
│                    Debian 12 – Sovereign Shield                       │
│                                                                      │
│   ┌──────────────────────────────────────────────────────────────┐   │
│   │ Network Interfaces                                            │   │
│   │---------------------------------------------------------------│   │
│   │  ens33  (WAN) : XX.X.X.X                                     │   │
│   │  ens37  (LAN) : XX.X.X.X                                      │   │
│   └──────────────────────────────────────────────────────────────┘   │
│                                                                      │
│   ROLES (progressively enabled)                                       │
│   ------------------------------------------------                   │
│   [ ] WAN ↔ LAN Gateway                                               │
│   [ ] Network Observation Point                                      │
│   [ ] Security Decision Point                                        │
│   [ ] Response Point (Isolation)                                     │
│                                                                      │
│   TECHNOLOGIES (FUTURE PHASES)                                        │
│   ------------------------------------------------                   │
│   - K3s (single-node)                                                 │
│   - Cilium (eBPF dataplane)                                          │
│   - Hubble (Network Visibility)                                      │
│                                                                      │
└───────────────────┬──────────────────────────────────────────────────┘
                    │
                    │  Controlled East–West Traffic
                    │
┌───────────────────▼──────────────────────────────────────────────────┐
│                        🛡️ PROTECTED ZONE / LAN                        │
│                        NETWORK: XX.X.X.X/XX                          │
│                                                                      │
│   ┌──────────────────────────────┐                                   │
│   │  Metasploitable3              │                                   │
│   │------------------------------│                                   │
│   │  IP        : XX.X.X.X        │                                   │
│   │  Interface : eth0             │                                   │
│   │                              │                                   │
│   │  Exposed Services:            │                                   │
│   │   • Vulnerable HTTP           │                                   │
│   │   • Legacy Services           │                                   │
│   │                              │                                   │
│   │  Security Role:               │                                   │
│   │   • Attacker Entry Point      │                                   │
│   │   • Intentionally Compromised │
│   │     Host                      │
│   └──────────────────────────────┘                                   │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
```

### 📂 Repository Structure

```
Sovereign-Shield/
├── ansible/
│   ├── inventory/
│   │   ├── inventory.ini
│   │   ├── v2-inventory.ini
│   │   └── v2-inventory.example.ini
│   │
│   ├── vars/
│   │   ├── global_config.yml
│   │   └── production_params.yml
│   │
│   ├── playbooks/
│   │   ├── deploy_shield.yml
│   │   ├── incident-response/
│   │   │   ├── isolate_node.yml
│   │   │   ├── revoke_secrets.yml
│   │   │   └── gather_evidence.yml
│   │   └── advanced/
│   │       └── ...
│   │
│   ├── roles/
│   │   ├── cilium/
│   │   │   └── ...
│   │   └── containment/
│   │       └── ...
│   │
│   └── simulations/
│       ├── lateral_movement/
│       ├── data_exfiltration/
│       └── malware_behavior/
│
├── policies/
│   └── ...
│
└── docs/
    └── purple-team-guide.md
```



**Core Technologies**

- Hypervisor: VMware
- Operating Systems: Debian, Kali, AlmaLinux, Windows Server
- Kubernetes: K3s
- Networking & Security: Cilium (eBPF)
- Observability: Hubble
- Automation & IR: Ansible

---

## 🧪 Implementation Roadmap

### Phase 1 — Infrastructure & Segmentation

- LAN / WAN network segmentation
- Virtual machine deployment
- Ansible inventory configuration
- Inter-node connectivity validation

**Outputs**
- Network diagrams
- Functional Ansible inventory

---

### Phase 2 — Shield Deployment

- Install K3s **without default CNI**
- Deploy Cilium (eBPF + IPAM)
- Enable Hubble for real-time visibility

**Outputs**
- Operational K3s cluster
- Observable network flows in Hubble UI

---

### Phase 3 — Active Defense (L7)

- Enforce HTTP L7 policies (GET / POST / PUT)
- DNS visibility for C2 detection
- Intent-based application filtering

**Outputs**
- Cilium policy YAML files
- Evidence of L7 enforcement

---

### Phase 4 — Red & Blue Operations

- Simulated attacks from Kali (scan, brute force)
- Analysis of dropped flows via Hubble
- Automated quarantine using Ansible playbooks

**Outputs**
- Dropped-flow captures
- Incident response logs

---

### Phase 5 — Governance & Purple Loop

- Document attacks and countermeasures
- Tune detection and enforcement policies
- Continuous improvement driven by Red Team results

---

## 🚀 MVP — Minimum Viable Product

**Goal:** Demonstrate a full **Attack → Detection → Response** chain.

### MVP Scope

- 1 single-node K3s cluster
- 1 simple HTTP service
- 1 Kali Linux attacker
- 1 restrictive L7 policy
- 1 Ansible quarantine playbook

### MVP Scenario

1. Kali sends an unauthorized HTTP request
2. Cilium blocks the request at L7
3. Hubble displays the blocked flow
4. Ansible isolates the compromised VM

**Success Criteria**

- Blocked flow visible in Hubble
- Policy enforcement confirmed
- Automated isolation executed

---

## 🧭 Alignment

### SOC Analysis
- Network traffic analysis
- Anomaly detection
- Incident investigation
- MITRE ATT&CK mapping

### Cloud / Kubernetes Security
- Secure cluster design
- Advanced network policies
- Zero Trust / Least Privilege
- eBPF observability

### DevSecOps
- Infrastructure as Code (Ansible)
- Security automation
- Incident response orchestration
- Governance and continuous improvement

---

## 📌 Project Value

- Realistic, hands-on cybersecurity lab
- Modern technologies
- A purple Team methodology

---

## 📸 Documentation & description (des_CRx(ip/'een')_tion)
### Documentation
**🧪 Key Commands — Version 1.0 (Complexyfy Not Crazyfy)
... In prgress

### Description
... In prgress


