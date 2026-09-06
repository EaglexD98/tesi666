# Extracción de datos para gráficas

Esta guía sirve para llevar los resultados a otra computadora sin instalar
OMNeT++ ni SUMO. Se probó con los 30 runs TCP y los 30 runs UDP de
`TCP_TOTO_HIGH` y `UDP_TOTO_HIGH`.

## Qué copiar

Desde este repositorio copia manteniendo los nombres:

```text
wifi5g-modulecreation/simulations/results/high/
wifi5g-modulecreation/scripts/compute_cost_function_metrics.py
wifi5g-modulecreation/Context/hybrid_cost_function_metrics_methodology.md
```

Los resultados crudos son los `.sca`, `.vec` y CSV dentro de `results/high`.
Los `.sca` contienen escalares y parámetros; los `.vec` contienen series de
corriente; los CSV contienen entregas, retrasos, ETA, colas y eventos.

## Generar la tabla para graficar

Desde la raíz de `wifi5g-modulecreation`:

```bash
python3 scripts/compute_cost_function_metrics.py \
  --results-dir simulations/results/high \
  --out-dir analysis/cost_function_metrics_high \
  --skip-module-tx-scan
```

`--skip-module-tx-scan` evita leer los `.vec`, que pueden ocupar varios GB.
La tabla resultante contiene energía, PDR, goodput, retrasos, retransmisiones
y métricas de TOTO separadas por configuración y transporte:

```text
analysis/cost_function_metrics_high/cost_function_metrics.csv
analysis/cost_function_metrics_high/warnings.csv
```

Debe haber 60 filas: 30 `TCP_TOTO_HIGH` y 30 `UDP_TOTO_HIGH`. No mezclar TCP
con UDP al calcular medias, desviaciones o intervalos de confianza.

Para incluir `FiveGModuleTxActiveTimeS` desde los vectores, ejecutar sin
`--skip-module-tx-scan`:

```bash
python3 scripts/compute_cost_function_metrics.py \
  --results-dir simulations/results/high \
  --out-dir analysis/cost_function_metrics_high_full
```

## Ejemplo mínimo con pandas

```python
import pandas as pd

f = "analysis/cost_function_metrics_high/cost_function_metrics.csv"
df = pd.read_csv(f)

tcp = df[df["transport"] == "tcp"]
udp = df[df["transport"] == "udp"]

summary = (df.groupby(["transport", "config_name"])
             [["PDR", "E_wifi_J", "E_5g_J",
               "wifi_full_route_goodput_bps",
               "fiveg_full_route_goodput_bps"]]
             .agg(["mean", "std"]))
print(summary)
```

Las unidades principales son: energía en `J`, goodput en `bps`, retrasos/AoI
en segundos y energía por bit en `uJ/bit`. Los contadores nativos 5G marcados
`Bps` son bytes/s; multiplicar por 8 solo al convertirlos a bits/s.

## Validación obligatoria

Antes de graficar, abrir `warnings.csv`. Una advertencia `STALE per-packet
CSV` significa que las métricas derivadas de esos CSV no deben usarse para ese
run hasta corregir o regenerar sus archivos. Las columnas provenientes del
`.sca` permanecen separadas, pero no deben mezclarse silenciosamente con una
fila que tenga CSV inválidos.

El análisis es posterior a la simulación: nunca vuelve a ejecutar OMNeT++ y
solo escribe dentro de `--out-dir`.
