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




ssss


xxxx



| Source     | Destination       | Protocol  | Action       |
| ---------- | ----------------- | --------- | ------------ |
| Pod Tracer | Internet (Google) | HTTP 80   | DROPPED ❌    |
| Pod Tracer | Windows VM        | HTTP GET  | ALLOWED ✅    |
| Pod Tracer | Windows VM        | HTTP POST | REJECTED 🛡️ |
