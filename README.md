# Asteroids

Un clone du célèbre jeu d'arcade **Asteroids** (Atari, 1979), écrit en **C** avec la bibliothèque **[raylib](https://www.raylib.com/)**.

Pilotez votre vaisseau dans un champ d'astéroïdes, détruisez-les avant qu'ils ne vous percutent, et survivez au plus grand nombre de vagues possible.

<!-- Ajoute ici une capture d'écran du jeu, par exemple : ![Capture du jeu](screenshot.png) -->

---

## Jouer

### Télécharger le jeu (Windows)

1. Va dans la section **[Releases](../../releases)** de ce dépôt.
2. Télécharge le fichier `.zip` de la dernière version.
3. Décompresse-le **dans un dossier**, puis lance `Asteroids.exe`.

> Les fichiers sons (`.wav` et `.ogg`) doivent rester dans le même dossier que `Asteroids.exe`, sinon le jeu sera muet.

> Au premier lancement, Windows peut afficher « Windows a protégé votre ordinateur », car le programme n'est pas signé. Clique sur **Informations complémentaires**, puis **Exécuter quand même**.

### Commandes

| Action | Clavier AZERTY | Clavier QWERTY |
|---|---|---|
| Tourner à gauche | `Q` | `A` |
| Tourner à droite | `D` | `D` |
| Accélérer | `Z` | `W` |
| Freiner | `S` | `S` |
| Tirer (maintenir pour tirer en rafale) | `Espace` | `Espace` |
| Lancer / relancer une partie | `Entrée` | `Entrée` |
| Quitter | `Échap` | `Échap` |

### Règles

- Le vaisseau garde son **inertie** : il continue sur sa lancée quand vous n'accélérez plus, et sa vitesse est limitée.
- Le vaisseau, les astéroïdes et les tirs qui sortent d'un côté de l'écran **réapparaissent de l'autre**… sauf vos tirs, qui disparaissent.
- Un **gros** astéroïde touché se divise en deux **moyens**, qui se divisent à leur tour en deux **petits**. Les petits sont détruits pour de bon.
- Points gagnés par astéroïde détruit :

  | Taille | Points |
  |---|---|
  | Gros | 1 |
  | Moyen | 2 |
  | Petit | 3 |

- Toucher un astéroïde coûte **une vie**. Le vaisseau devient alors **invulnérable** quelques secondes (il clignote), le temps de s'éloigner.
- Quand tous les astéroïdes sont détruits, une **nouvelle vague** apparaît, avec plus d'astéroïdes que la précédente.
- La partie se termine quand vous n'avez plus de vie. Le but : faire le **meilleur score** possible !

---

## Compiler depuis les sources

### Prérequis

- Un compilateur C (testé avec **GCC / MinGW-w64**)
- **[raylib](https://github.com/raysan5/raylib/releases)** (version précompilée `win64_mingw-w64`)
- Facultatif : **[Code::Blocks](https://www.codeblocks.org/)**, avec le fichier de projet `Asteroids.cbp` fourni

### Options de compilation

Indique au compilateur les dossiers `include` et `lib` de raylib, puis ajoute ces options au linker :

```
-lraylib -lopengl32 -lgdi32 -lwinmm
-Wl,--defsym,stat64i32=_stat64
```

La dernière ligne corrige une incompatibilité connue entre certaines versions précompilées de raylib et le compilateur fourni avec Code::Blocks.

### Organisation du code

| Fichier | Rôle |
|---|---|
| `main.c` | Fenêtre, boucle principale et états du jeu (accueil, partie, fin) |
| `config.h` | Réglages du jeu (taille de l'écran, vitesses, durées…) |
| `ship.c` / `ship.h` | Le vaisseau : déplacement, rotation, inertie, dessin |
| `asteroid.c` / `asteroid.h` | Les astéroïdes : création, vagues, déplacement, dessin |
| `missiles.c` / `missiles.h` | Les tirs |
| `collisions.c` / `collisions.h` | Détection des collisions entre cercles |
| `game.c` / `game.h` | États du jeu et remise à zéro d'une partie |

La plupart des réglages (vitesses, nombre de vies, cadence de tir, portée des tirs…) se modifient directement dans `config.h`.

---

## Crédits

- Moteur graphique et audio : **[raylib](https://www.raylib.com/)**, par Ramon Santamaria
- Son de propulsion : pack **Sci-Fi Sounds** de **[Kenney](https://kenney.nl/)** (licence CC0)
- Son de tir : généré avec **[jsfxr](https://sfxr.me/)**
- Jeu original : **Asteroids**, Atari (1979)
