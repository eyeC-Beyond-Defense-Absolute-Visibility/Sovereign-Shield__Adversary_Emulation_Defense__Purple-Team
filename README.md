🛡️ Sovereign Shield
	🛠️ Display Note / Note d'affichage : If the formatting looks broken, try viewing the [Raw file] or the Blame view --- Si le formatage semble incorrect, essayez de visualiser le fichier Brut (Raw) ou le mode Blame.

Phase I: The Foundations



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
	- Goal: Deploy the nodes for the security lab --- Objectif : Déployer les nœuds pour le laboratoire de sécurité.
Machine			OS				Role							RAM
Control-Plane	Debian/Kali		K3s Master & Cilium				4GB+
Target-Win		Windows 10/11	Attack Target / Cible d'attaque	4GB

Important Points --- Points importants:
 - Ensure all VMs are on the same NAT/Internal network --- S'assurer que toutes les VMs sont sur le même réseau NAT/Interne.
 - Memory Check: K3s + Cilium require at least 4GB of RAM to compile eBPF programs --- Vérification RAM : K3s + Cilium nécessitent au moins 4Go de RAM pour compiler les programmes eBPF.



🛡️ 3. Goal: Install K3s without default networking and replace it with Cilium (eBPF) --- Objectif : Installer K3s sans réseau par défaut et le remplacer par Cilium (eBPF).
	 a- Install K3s without Flannel/Kube-proxy --- Installer K3s sans Flannel ni Kube-proxy
  		sudo curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="--flannel-backend=none --disable-network-policy --disable traefik" sh -
	 b- Export the cluster configuration --- Exporter la configuration du cluster
 		 export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
	 c- Install Cilium CLI & deploy the agent --- Installer le CLI Cilium et déployer l'agent
  		sudo -E cilium install --set k8sServiceHost=127.0.0.1 --set k8sServicePort=6443
	 d- Enable Hubble for visibility --- Activer Hubble pour la visibilité
  		sudo -E cilium hubble enable --ui



🧪 4. Testing the Shield --- Test du Bouclier
	- Goal: Verify that the policy effectively blocks unauthorized traffic --- Objectif : Vérifier que la politique bloque efficacement le trafic non autorisé.
		- Step 1: Create a test pod --- Créer un pod de test: 
			- sudo k3s kubectl run tracer --image=curlimages/curl -- sh -c "while true; do curl -sL google.com > /dev/null; sleep 2; done"
		- Step 2: Apply the Security Policy --- Appliquer la politique de sécurité
			- sudo k3s kubectl apply -f shield-policy.yaml



Conclusion: Visual Verification --- Vérification visuelle
 Enter this command in your kali terminal --- Entrer cette commande dans votre terminal kali: sudo -E cilium hubble ui
	Expected Result: Red lines in Hubble UI, "dropped" status for traffic to 'world'.
	---
	Résultat attendu : Lignes rouges dans l'interface Hubble, statut "dropped" pour le trafic vers 'world'.



🏁 End of Phase 1 -- Fin de la Phase 1 : récapitulatif
  Infrastructure : Functional K3s cluster with Cilium --- Cluster K3s fonctionnel avec Cilium.
  Observability: Hubble configured and used to validate real-time streams --- Observabilité : Hubble configuré et utilisé pour valider les flux en temps réel.
  Micro-segmented Security: Implementation of a strict Zero-Trust perimeter (L3/L4 and L7) --- Sécurité Micro-segmentée : Mise en place d'un périmètre Zero-Trust strict (L3/L4 et L7).

Source		Destination			Protocole	Action
Pod Tracer	Google / Internet	HTTP (80)	DROPPED ❌
Pod Tracer	VM Windows (129)	HTTP GET	ALLOWED ✅
Pod Tracer	VM Windows (129)	HTTP POST	REJECTED (L7) 🛡️

SCREENSHOTS --- CAPTURES D'ÉCRAN:

The "Before" State: Open Communication --- Avant l'application du bouclier, le cluster est en mode ouvert (comportement par défaut de Kubernetes).
	> Baseline Observability: Traffic Flowing Without Restrictions
		--> * Initial visualization in Hubble UI. Note that all egress traffic to world is marked green (forwarded), indicating that no restrictions are active yet.
		--> * Visualisation initiale dans Hubble UI. On remarque que tout le trafic sortant vers world est marqué en vert (forwarded), indiquant qu'aucune restriction n'est encore active.
		<img width="3391" height="1743" alt="W1-Capture" src="https://github.com/user-attachments/assets/19b1428e-5f39-4f69-9275-6beebf011506" />

---

The "After" State: Zero-Trust Implementation --- Le bouclier eBPF est activé. Le trafic est désormais filtré selon nos règles de sécurité.
	> Egress Lockdown: Blocking Unauthorized External Traffic
			--> * Security policy enforcement. Hubble instantly shows red lines towards world. The status changes to dropped, proving the pod can no longer communicate with the outside world.
			--> * Application de la politique de sécurité. Hubble montre instantanément des lignes rouges vers world. Le statut passe à dropped, prouvant que le pod ne peut plus communiquer avec l'extérieur.
			<img width="3377" height="1744" alt="W2-Capture" src="https://github.com/user-attachments/assets/a354abd1-cf00-4424-bd52-59fe0560d2bc" />

---

Layer 7 Deep Packet Inspection --- Filtrage au niveau de l'application (HTTP).
	> Advanced L7 Security: Granular HTTP Method Filtering
		--> * Validation finale du bouclier. Le trafic vers la VM Windows est autorisé pour les requêtes GET (vert), mais Cilium intercepte et bloque les tentatives POST (timeout/reset), empêchant toute exfiltration de données illicite.
		--> * Final shield validation. Traffic to the Windows VM is allowed for GET requests (green), but Cilium intercepts and blocks POST attempts (timeout/reset), preventing unauthorized data exfiltration.
		<img width="3401" height="1875" alt="W3-Capture" src="https://github.com/user-attachments/assets/8c0b8c4e-7963-4085-9fdb-172d39d1f0ff" />

---

Advanced Security: Deep Packet Inspection (L7 --- La preuve ultime de la puissance de Cilium : le filtrage au niveau applicatif.
	> Layer 7 Enforcement: Selective HTTP Method Filtering
		--> Validation finale du bouclier. Le trafic vers la VM Windows est autorisé pour les requêtes GET (vert), mais les tentatives POST sont bloquées par le proxy eBPF (connection timeout), empêchant toute exfiltration de données.
		--> Final shield validation. Traffic to the Windows VM is allowed for GET requests (green), but POST attempts are blocked by the eBPF proxy (connection timeout), preventing unauthorized data exfiltration.
		<img width="3380" height="1724" alt="WX-Capture" src="https://github.com/user-attachments/assets/05d433a2-06ca-4bad-a697-3ff814dc857d" />


