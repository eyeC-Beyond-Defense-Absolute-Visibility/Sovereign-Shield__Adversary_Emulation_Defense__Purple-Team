# 🛡️ Sovereign Shield

> **Display note / Note d’affichage**  
> If the formatting looks broken, try viewing the **Raw file** or the **Blame view**.  
> Si le formatage semble incorrect, essayez de visualiser le fichier **Raw** ou le mode **Blame**.

---

## 🔰 Phase I — Foundations

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
🧰 Requirements — Prérequis

Kali, Debian and Windows VMs (NAT / Internal Network)

Ansible

Note
Ansible is used to automate node configuration.
Ansible permet d’automatiser la configuration des nœuds.

📋 1. Ansible Setup — Installation d’Ansible

Goal / Objectif
Install the orchestration tool on the control machine (Kali).
Installer l’outil d’orchestration sur la machine de contrôle (Kali).
```
sudo apt update && sudo apt install ansible -y
ansible --version
```
🏗️ 2. VM Provisioning — Création des machines virtuelles

Goal / Objectif
Deploy nodes for the security lab.
| Machine       | OS              | Role                            | RAM  |
| ------------- | --------------- | ------------------------------- | ---- |
| Control-Plane | Debian / Kali   | K3s Master & Cilium             | 4GB+ |
| Target-Win    | Windows 10 / 11 | Attack Target / Cible d’attaque | 4GB  |

⚠️ Important Notes

All VMs must be on the same NAT / Internal network

K3s + Cilium require at least 4GB RAM to compile eBPF programs


