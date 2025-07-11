# iot-esp32


mermaid : 


---
title: node
---

flowchart TD
    id1["`setup()`"]
    id2["`loop()`"]

    subgraph 1
    id1 --> id2
    end

    id3["`everyX()`"]
    id3-1["`coordPipeline()`"]

    subgraph 2
    id3 -.- id3-1
    end

    id2 --> 2
     
    id4@{ shape: doc, label: "PIPELINE_GLOBAL.cpp" }

    id3-1 --> id4

    subgraph 3
    id5["`pipelineSwitchGlobal()`"]
    end

    id4 --> 3

    A@{ shape: odd, label: "STEP_INIT_GLOBAL" }
    B@{ shape: odd, label: "STEP_GNSS" }
    C@{ shape: odd, label: "STEP_SEND_4G" }
    D@{ shape: odd, label: "STEP_END_GLOBAL" }

     %% Assignation de classes
    class A stepInit;
    class B stepGNSS;
    class C step4G;
    class D stepEnd;

    %% Définition des styles
    classDef stepInit fill:#d0e6ff,stroke:#1e90ff,stroke-width:2px;
    classDef stepGNSS fill:#eaffd0,stroke:#2e8b57,stroke-width:2px;
    classDef step4G fill:#fff0d0,stroke:#ff8c00,stroke-width:2px;
    classDef stepEnd fill:#ffd0d0,stroke:#dc143c,stroke-width:2px;

    subgraph 3-1
    A --> B --> C --> D
    B === ex1 --> ex2 --> ex3 
    C === ex4 --> ex5
    end

    

    id5 --> 3-1

    ex1["`gnssPowerOn`"]
    ex2["`DisplayLatLngInfo`"]
    ex3["`gnssPowerOff`"]

    ex4["`setup_CATM1()`"]
    ex5["`sendMessageCBOR(getCoordonneesDepuisEEPROM().c_str())`"]

    ex1 ===|utilise| MachineEtat
    ex2 ===|execute| id["`mettre les coords dans vector`"]
    ex3 ===|utilise| MachineEtat

    IDLE[[IDLE<br>Initialisation]]
    SENDING[[SENDING<br>Envoi commande]]
    WAITING_RESPONSE[[WAITING_RESPONSE<br>Analyse réponse]]
    RETRY[[RETRY<br>Nouvelle tentative]]
    ERROR[[ERROR<br>Erreur terminale]]
    END[[END<br>Tâche terminée]]

    subgraph MachineEtat
        IDLE -->|Prépare et envoie commande| SENDING
        SENDING -->|Commande envoyée| WAITING_RESPONSE

        WAITING_RESPONSE -->|Réponse OK trouvée| END
        WAITING_RESPONSE -->|Pas de réponse<br>avant TIMEOUT| RETRY

        RETRY -->|Nouvelle tentative si retry < max| SENDING
        RETRY -->|Échec max tentatives| ERROR

        ERROR -->|Fin avec erreur| END
    end
        ERROR --> GestionErreur
    subgraph GestionErreur
        A1[Entrée dans case ERROR]
        B1{Callback défini ?}
        C1["`Appel du callback\ntask.onErrorCallback(task)`"]
        D1["`Comportement par défaut\nstate=IDLE,\nretryCount=0,\nresponseBuffer=\nisFinished=false`"]
        E1[Retourner false]

        A1 --> B1
        B1 -- Oui --> C1
        B1 -- Non --> D1
        C1 --> E1
        D1 --> E1
    end

    C1 -->|callback| ex1 -->|callback| B
    

    style IDLE fill:#dfefff,stroke:#339
    style SENDING fill:#e7ffe7,stroke:#393
    style WAITING_RESPONSE fill:#fffbdc,stroke:#999100
    style RETRY fill:#fff0e6,stroke:#d47a00
    style ERROR fill:#ffe6e6,stroke:#cc0000
    style END fill:#e6ffe6,stroke:#009900
