🛡️ Sovereign Shield

	🛠️ Display Note / Note d'affichage :If the formatting looks broken, try viewing the [Raw file] or the Blame view. --- Si le formatage semble incorrect, essayez de visualiser le fichier Brut (Raw) ou le mode Blame.
	

Phase 1: The Foundations



Project structure --- Structure du projet



└── ansible/
    ├── scripts/           # For your .yml playbooks and bash scripts --- Pour tes playbooks .yml et scripts bash
    │   ├── deploy_shield.yml
    │   └── enable_hubble.yml
    ├── policies/          # For your Cilium .yaml rule files --- Pour tes fichiers de règles Cilium .yaml
    │   └── shield-policy.yaml
    └── inventory.ini      # To list your target machines --- Pour lister tes machines cibles



What you need to get started --- Ce dont vous avez besoin pour commencer: 
 - Kali, Debian and Windows (NAT in NAT mode --- En mode NAT)
 - Ansible



This document describes the setup of the core infrastructure and the eBPF firewall. --- Ce document décrit la mise en place de l'infrastructure de base et du pare-feu eBPF.



📋 1. Ansible Setup --- Préparation & Installation d'Ansible
Goal: Install the orchestration tool on your control machine (Kali) --- Objectif : Installer l'outil d'orchestration sur votre machine de contrôle (Kali).
 # Update the system and install Ansible --- Mettre à jour le système et installer Ansible
   sudo apt update && sudo apt install ansible -y

 # Verify the installation --- Vérifier l'installation
   ansible --version

Note: Ansible will allow us to automate the configuration of our future nodes.
Note : Ansible nous permettra d'automatiser la configuration de nos futurs nœuds.



🏗️ 2. VM Provisioning --- Création des Machines Virtuelles
Goal: Deploy the nodes for the security lab --- Objectif : Déployer les nœuds pour le laboratoire de sécurité.
Machine			OS				Role							RAM
Control-Plane	Debian/Kali		K3s Master & Cilium				4GB+
Target-Win		Windows 10/11	Attack Target / Cible d'attaque	4GB

Important Points --- Points importants:
 - Ensure all VMs are on the same NAT/Internal network --- S'assurer que toutes les VMs sont sur le même réseau NAT/Interne.
 - Memory Check: K3s + Cilium require at least 4GB of RAM to compile eBPF programs --- Vérification RAM : K3s + Cilium nécessitent au moins 4Go de RAM pour compiler les programmes eBPF.



🛡️ 3. Install K3s without default networking and replace it with Cilium (eBPF) --- Objectif : Installer K3s sans réseau par défaut et le remplacer par Cilium (eBPF).
	 # a. Install K3s without Flannel/Kube-proxy --- Installer K3s sans Flannel ni Kube-proxy
  		sudo curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="--flannel-backend=none --disable-network-policy --disable traefik" sh -
	 # b. Export the cluster configuration --- Exporter la configuration du cluster
 		 export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
	 # c. Install Cilium CLI & deploy the agent --- Installer le CLI Cilium et déployer l'agent
  		sudo -E cilium install --set k8sServiceHost=127.0.0.1 --set k8sServicePort=6443
	 # d. Enable Hubble for visibility --- Activer Hubble pour la visibilité
  		sudo -E cilium hubble enable --ui



🧪 4. Testing the Shield --- Test du Bouclier
Goal: Verify that the policy effectively blocks unauthorized traffic --- Objectif : Vérifier que la politique bloque efficacement le trafic non autorisé.
 Step 1: Create a test pod --- Créer un pod de test: 
 	sudo k3s kubectl run tracer --image=curlimages/curl -- sh -c "while true; do curl -sL google.com > /dev/null; sleep 2; done"
 Step 2: Apply the Security Policy --- Appliquer la politique de sécurité
 	sudo k3s kubectl apply -f shield-policy.yaml



Conclusion: Visual Verification --- Vérification visuelle
 Enter this command in your kali terminal --- Entrer cette commande dans votre terminal kali: sudo -E cilium hubble ui
	Expected Result: Red lines in Hubble UI, "dropped" status for traffic to 'world'.
	---
	Résultat attendu : Lignes rouges dans l'interface Hubble, statut "dropped" pour le trafic vers 'world'.




🏁 End of Phase 1 -- Fin de la Phase 1 : récapitulatif
  Infrastructure : Functional K3s cluster with Cilium --- Cluster K3s fonctionnel avec Cilium.
  Observability: Hubble configured and used to validate real-time streams --- Observabilité : Hubble configuré et utilisé pour valider les flux en temps réel.
  Micro-segmented Security: Implementation of a strict Zero-Trust perimeter (L3/L4 and L7) --- Sécurité Micro-segmentée : Mise en place d'un périmètre Zero-Trust strict (L3/L4 et L7).
<<<<<<< HEAD

Source		Destination			Protocole	Action
=======
  
Source		Destination		Protocole	Action
>>>>>>> 800b8b4 (Add inventory example and update documentation)
Pod Tracer	Google / Internet	HTTP (80)	DROPPED ❌
Pod Tracer	VM Windows (129)	HTTP GET	ALLOWED ✅
Pod Tracer	VM Windows (129)	HTTP POST	REJECTED (L7) 🛡️


What has been accomplished with SSH between Kali and Debian
Ansible operates without agents. To configure the Debian machine (the future K3s Master) from your Kali machine (the Control Plane), Ansible needs to be able to connect remotely.

Automation: Without an SSH key, Ansible would ask for your password for every micro-task.
The secure channel: SSH creates an encrypted tunnel to send the K3s and Cilium installation commands.
---
Ce qui a été ralisé SSH entre Kali et Debian
Ansible fonctionne sans agent (agentless). Pour configurer la machine Debian (le futur Master K3s) depuis ta Kali (le Control Plane), Ansible doit pouvoir se connecter à distance.
  L'automatisation : Sans clé SSH, Ansible te demanderait ton mot de passe à chaque micro-tâche.
  Le canal sécurisé : SSH crée un tunnel chiffré pour envoyer les commandes d'installation de K3s et Cilium.
  
SCREENSHOTS --- CAPTURES D'ÉCRAN:


