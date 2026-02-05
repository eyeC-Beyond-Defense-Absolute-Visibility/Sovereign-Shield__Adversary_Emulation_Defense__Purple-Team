# 🛡️ Sovereign Shield
![K3s](https://img.shields.io/badge/Kubernetes-K3s-326ce5?logo=kubernetes&logoColor=white)
![Cilium](https://img.shields.io/badge/Cilium-eBPF-ffcc00?logo=cilium&logoColor=black)
![eBPF](https://img.shields.io/badge/Linux-eBPF-000000?logo=linux&logoColor=white)
![Security](https://img.shields.io/badge/Security-Zero--Trust-red)
![Status](https://img.shields.io/badge/Phase-I%20Complete-success)
![Status](https://img.shields.io/badge/Phase-I%20In%20Progress-yellow)


> **Display note / Note d’affichage**  
> If the formatting looks broken, try viewing the **Raw file** or the **Blame view**.  
> Si le formatage semble incorrect, essayez de visualiser le fichier **Raw** ou le mode **Blame**.

---

# 🔰 Phase I — Foundations

This phase describes the setup of the **core infrastructure** and an **eBPF-based firewall** using **K3s + Cilium**.  
Cette phase décrit la mise en place de l’**infrastructure de base** et d’un **pare-feu eBPF** avec **K3s + Cilium**.

---

## 📁 Project Structure — Structure du projet

```
ansible/
├── scripts/              # Ansible playbooks & bash scripts
│   ├── deploy_shield.yml
│   └── enable_hubble.yml
├── policies/             # Cilium security policies (.yaml)
│   └── shield-policy.yaml
└── inventory.ini         # Target machines inventory
```
## 🧰 Requirements — Prérequis

Kali, Debian and Windows VMs (NAT / Internal Network)

Ansible

Note
Ansible is used to automate node configuration.
Ansible permet d’automatiser la configuration des nœuds.

### 📋 1. Ansible Setup — Installation d’Ansible

Goal / Objectif
Install the orchestration tool on the control machine (Kali).
Installer l’outil d’orchestration sur la machine de contrôle (Kali).
```
sudo apt update && sudo apt install ansible -y
ansible --version
```

```
[k8s_nodes]
# EN: The heart of the shield (K3s Cluster + Cilium eBPF)
# FR: Le cœur du bouclier (Cluster K3s + Cilium eBPF)
debian-shield ansible_host=192.16X.XX.XXX ansible_user=your_username

[attackers]
# EN: Threat 1: Potentially compromised Linux server
# FR: Menace 1: Serveur Linux potentiellement compromis
ubuntu-server ansible_host=192.16X.XX.XXX ansible_user=your_username

# EN: Threat 2: The ultimate vulnerable machine for your penetration tests
# FR: Menace 2: La machine vulnérable par excellence pour tes tests de pénétration
metasploitable ansible_host=192.16X.XX.XXX ansible_user=your_username

[targets]
# EN: The critical target to protect (Sensitive / Sovereign Data)
# FR: La cible critique à protéger (Données sensibles / Données souveraines)
windows-target ansible_host=192.16X.XX.XXX ansible_user=your_username

[all:vars]
# EN: Define the Python interpreter for all hosts
# FR: Définir l'interpréteur Python pour tous les hôtes
ansible_python_interpreter=/usr/bin/python3

# EN: Optional: Ignore SSH key verification for your local lab
# FR: Optionnel: ignore la vérification des clés SSH pour ton lab local
ansible_ssh_common_args='-o StrictHostKeyChecking=no'
```

### 🏗️ 2. VM Provisioning — Création des machines virtuelles

Goal / Objectif
Deploy nodes for the security lab.
| Machine       | OS              | Role                            | RAM  |
| ------------- | --------------- | ------------------------------- | ---- |
| Control-Plane | Debian / Kali   | K3s Master & Cilium             | 4GB+ |
| Target-Win    | Windows 10 / 11 | Attack Target / Cible d’attaque | 4GB  |

### ⚠️ Important Notes

All VMs must be on the same NAT / Internal network

K3s + Cilium require at least 4GB RAM to compile eBPF programs

### 🛡️ 3. K3s + Cilium (eBPF Firewall)

Goal / Objectif
Install K3s without default networking and replace it with Cilium (eBPF).

Install K3s (No Flannel / No kube-proxy)
```
curl -sfL https://get.k3s.io | \
INSTALL_K3S_EXEC="--flannel-backend=none --disable-network-policy --disable traefik" \
sh -
```

Export Cluster Configuration
```
export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
```

Install Cilium & Enable Hubble
```
cilium install \
  --set k8sServiceHost=127.0.0.1 \
  --set k8sServicePort=6443

cilium hubble enable --ui
```
### 🧪 4. Testing the Shield — Tests du bouclier

Goal / Objectif
Verify that the security policy blocks unauthorized traffic.

#### Step 1 — Create a Test Pod
```
k3s kubectl run tracer \
  --image=curlimages/curl \
  -- sh -c "while true; do curl -sL google.com > /dev/null; sleep 2; done"
```


#### Step 2 — Apply the Security Policy
```
k3s kubectl apply -f shield-policy.yaml

```


#### 👀 Visual Verification — Vérification visuelle

Launch Hubble UI:
```
cilium hubble ui

```


## 🏁 Phase I Summary — Récapitulatif
### ✅ Achievements

Infrastructure
Functional K3s cluster with Cilium

Observability
Hubble enabled for real-time flow analysis

Micro-Segmented Security
Zero-Trust perimeter enforced (L3 / L4 / L7)

| Source     | Destination       | Protocol  | Action       |
| ---------- | ----------------- | --------- | ------------ |
| Pod Tracer | Internet (Google) | HTTP 80   | DROPPED ❌    |
| Pod Tracer | Windows VM        | HTTP GET  | ALLOWED ✅    |
| Pod Tracer | Windows VM        | HTTP POST | REJECTED 🛡️ |

## 📸 Screenshots — Captures d’écran
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


# 🗺️ Phase II — Active Defense & Threat Containment

Welcome to the second evolution of **Sovereign Shield**.

In this phase, the project evolves from a **static Zero Trust perimeter** to an **active defense infrastructure** capable of **detecting, alerting, and containing threats in real time**.

This phase introduces:
- Explicit threat actors
- Automated orchestration
- Intrusion detection & prevention (IDS/IPS)
- Governance, Risk & Compliance (GRC) alignment

---

## 🖥️ Lab Environment Overview (VMware)

This phase is executed in a **hybrid virtualized laboratory** designed to simulate real-world attack paths and defensive controls.

> 📌 **VMware Workstation / ESXi Topology**  
<img width="3839" height="2293" alt="Screenshot of my VMware with used machines" src="https://github.com/user-attachments/assets/ee6b86a3-2c61-42f6-8853-a944fda849ec" />

The environment is intentionally segmented to:
- Simulate attacker pivoting
- Observe lateral movement
- Validate containment at the kernel level (eBPF)

---

## 🌿 Branch Strategy — Project Complexity Expansion

To preserve Phase I stability while enabling advanced experimentation, **Phase II is developed in a dedicated Git branch**.

> 🎯 **Why a new branch?**
- Introduce additional nodes and attack surfaces
- Experiment with automation and IDS/IPS logic
- Avoid regression on the foundational security baseline

<img width="1058" height="638" alt="creation of a new complexified branche named v2-active-defense-and-threat-containment" src="https://github.com/user-attachments/assets/d235b7b5-9c0f-42b7-b668-ac597f733d58" />


Example workflow:
```
git checkout -b phase-2-active-defense
```
🏗️ Part A — Automation (The Orchestrator)

This section focuses on Infrastructure as Code (IaC) and orchestration of a multi-node adversarial environment.

🌐 Hybrid Laboratory Architecture

Roles in the environment:

🛡️ The Shield
Debian node running K3s + Cilium (eBPF)
Acts as a network enforcement point and IPS

☠️ Threat Actors

Metasploitable2
Vulnerable system used to simulate exploitation attempts

Ubuntu Server
Potentially compromised node for lateral movement scenarios

🏛️ The Sovereign Data

Windows Target
High-value asset requiring strict protection

🛠️ Automation Scope

Automation is handled via Ansible, enabling repeatable and auditable deployments.

Key capabilities:

Unified Inventory
Centralized asset management via ansible/inventory.ini

Automated Shield Deployment
One-command installation of:

K3s

Cilium

Security policies

Health & Reachability Checks
Automated validation of connectivity and policy enforcement across all nodes

💡 Automation ensures consistency and reduces configuration drift — a critical requirement in regulated environments.

🛡️ Part B — Hardening & GRC (The Compliance Engine)

This section bridges technical enforcement with cybersecurity governance frameworks.

🔍 Intrusion Detection & Prevention (IDS / IPS)

eBPF-powered Detection
Cilium + Hubble monitor:

Port scans

Unauthorized service access

Suspicious east-west traffic

🪤 Ghost Pod (Honeypot)
A deliberately exposed Kubernetes pod designed to:

Attract malicious connections

Trigger high-severity alerts in Hubble

Validate detection logic without risking real assets

⚠️ Any interaction with the Ghost Pod is considered malicious by design.

| Security Control         | NIST CSF               | ISO 27001                     | SOC 2        |
| ------------------------ | ---------------------- | ----------------------------- | ------------ |
| **Micro-segmentation**   | PR.AC (Access Control) | A.13.1 (Network Security)     | Security     |
| **Real-time Monitoring** | DE.AE (Detection)      | A.12.4 (Logging & Monitoring) | Monitoring   |
| **Attack Containment**   | RS.RP (Response)       | A.16.1 (Incident Management)  | Availability |

🎯 This mapping demonstrates how technical controls support compliance objectives, not just security outcomes.

📸 Phase II — Proof of Concept

This section documents observable security outcomes.

🧪 Evidence will include:
- Hubble flow visualizations
- Blocked attack attempts
- Honeypot interaction alerts
- Policy enforcement under attack conditions

<!-- v2 SCREENSHOTS HERE -->

🚧 Status
Phase II is actively evolving as new automation and detection scenarios are introduced.

