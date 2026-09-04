# Reproduccion de `tesi666` en otra computadora

Este repositorio conserva el workspace fuente usado por la tesis. Los
resultados, vectores, binarios y directorios `out/` no se versionan porque son
regenerables y pueden ocupar decenas de GB.

## Versiones de referencia

- OMNeT++ 6.2.0
- INET 4.5.4 (fuente incluido y con los cambios del proyecto)
- Simu5G 1.4.1 (fuente incluido y modificado)
- Veins y Veins_INET incluidos en el workspace
- SUMO 1.18.0 en la maquina original

## Clonar

```bash
gh auth login -h github.com
gh auth setup-git
git clone --recurse-submodules https://github.com/EaglexD98/tesi666.git
cd tesi666
```

Si el clon se hizo sin submodulos:

```bash
git submodule update --init --recursive
```

## OMNeT++ mediante `opp_env`

Instalar primero Git, Python, `pipx` y SUMO. En Ubuntu/Debian:

```bash
sudo apt update
sudo apt install -y git gh pipx sumo sumo-tools
pipx ensurepath
pipx install opp-env
```

Cerrar y volver a abrir la terminal. Crear un workspace de `opp_env`, instalar
OMNeT++ 6.2.0 y clonar `tesi666` dentro del mismo directorio:

```bash
mkdir -p "$HOME/omnet-workspace"
cd "$HOME/omnet-workspace"
opp_env init
opp_env install omnetpp-6.2.0
gh auth login -h github.com
gh auth setup-git
git clone --recurse-submodules https://github.com/EaglexD98/tesi666.git tesi666
```

En la maquina original el entorno se activa con:

```bash
source "$HOME/omnet-workspace/omnetpp-6.2.0/setenv"
```

SUMO debe estar disponible en `PATH`. Para reproducir exactamente el entorno
actual se recomienda SUMO 1.18.x.

## Compilar el workspace

```bash
cd "$HOME/omnet-workspace"
opp_env run omnetpp-6.2.0 -c 'cd tesi666 && ./scripts/build_workspace.sh release'
```

El orden aplicado es INET, Veins, Veins_INET, Simu5G y finalmente
`wifi5g-modulecreation`.

## Ejecutar simulaciones

Leer primero:

```text
wifi5g-modulecreation/RUNBOOK_SIMULACIONES_PARA_CODEX.md
```

El runbook contiene configuraciones, semillas, bloques, limites de paralelismo,
respaldo, monitorizacion y validacion.
