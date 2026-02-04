🛡️ Sovereign Shield - Phase 1: The Foundations

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
Machine		OS		Role					RAM
Control-Plane	Debian/Kali	K3s Master & Cilium			4GB+
Target-Win	Windows 10/11	Attack Target / Cible d'attaque		4GB

Important Points --- Points importants:
 - Ensure all VMs are on the same NAT/Internal network --- S'assurer que toutes les VMs sont sur le même réseau NAT/Interne.
 - Memory Check: K3s + Cilium require at least 4GB of RAM to compile eBPF programs --- Vérification RAM : K3s + Cilium nécessitent au moins 4Go de RAM pour compiler les programmes eBPF.



🛡️ 3. Goal: Install K3s without default networking and replace it with Cilium (eBPF) --- Objectif : Installer K3s sans réseau par défaut et le remplacer par Cilium (eBPF).
 # a. Install K3s without Flannel/Kube-proxy --- Installer K3s sans Flannel ni Kube-proxy
  sudo curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="--flannel-backend=none --disable-network-policy --disable traefik" sh -
 # b. Export the cluster configuration --- Exporter la configuration du cluster
  export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
 # 3. Install Cilium CLI & deploy the agent --- Installer le CLI Cilium et déployer l'agent
  sudo -E cilium install --set k8sServiceHost=127.0.0.1 --set k8sServicePort=6443
 # 4. Enable Hubble for visibility --- Activer Hubble pour la visibilité
  sudo -E cilium hubble enable --ui



🧪 4. Testing the Shield --- Test du Bouclier
Goal: Verify that the policy effectively blocks unauthorized traffic --- Objectif : Vérifier que la politique bloque efficacement le trafic non autorisé.
 Step 1: Create a test pod --- Créer un pod de test: sudo k3s kubectl run tracer --image=curlimages/curl -- sh -c "while true; do curl -sL google.com > /dev/null; sleep 2; done"
 Step 2: Apply the Security Policy --- Appliquer la politique de sécurité [Create shield-policy.yaml:YAML] (content of file --- contenu du fichier):
	apiVersion: "cilium.io/v2"
	kind: CiliumNetworkPolicy
	metadata:
  	 name: "block-external-world"
	spec:
  	 endpointSelector:
    	  matchLabels:
      	   run: tracer
  	egress:
  	- toEntities: [cluster, kube-apiserver]

Apply it --- L'appliquer: sudo k3s kubectl apply -f shield-policy.yaml



Conclusion: Visual Verification --- Vérification visuelle
 Enter this command in your kali terminal --- Entrer cette commande dans votre terminal kali: sudo -E cilium hubble ui
	Expected Result: Red lines in Hubble UI, "dropped" status for traffic to 'world'.
	---
	Résultat attendu : Lignes rouges dans l'interface Hubble, statut "dropped" pour le trafic vers 'world'.

