# Web based RPG/strategie

Hráč bude spravovat vesnici, rozrůstat jí, sbýrat nové suroviny

## Začátek hry

Hra začíná se 12 lidmi a s 100 jednotkami potravin. Hráč bude přiřazovat volné lidi do práce, čímž bude generovat suroviny. Ze začaáku hry se bude jednat především o jednoduché suroviny a práce. Sběrači budou produkovat malé možství jídla, což bude znamenat, že pro uživení populace bude nezbytné aby většína lidí sbírala jídlo. Zbylích pár jedniců pak bude moci sbírat dřevo nebo kamení.

## Globální proměnné

1. rok = 40s - doporučené nastavení
2. populační růst $r_0 = 0.02$%/s
3. míra hladu $h_r=0.02$ jídla/s

## Populace (Pracovní síla)

Růst populace bude modelován pomocí nasledující rovnice:

$P = P_0×e^{rt}$

kde:

- $P$ - konečný stav populace
- $P_0$ - současný stav populace
- $r$ - desetiné číslo vyjadřující procentuaní růst populace v daném čase (u lidské populace se jedná zhruba o 2% ročně)
- $t$ - čas

Populační růst se vypočítává pomocí následující rovnice:

$r =r_0×h$

- $r_0$ - základní populační růst

- $h$ - koeficient štěstí, který se pohybuje v intervalu $⟨-1;1⟩$ a zavisí na průměrném štěstí $h_a$
- pro $h_a=⟨0;20)$ se $h=⟨-1;0)$
- pro $h_a=⟨20;80)$ se $h=⟨0,1)$
- pro $h_a>80$ se $h=1$

### Třída jedinec

- __Happiness__ - hodnota mezi 0 - 100 určuje jak moc je jedinec šťastný
- __Hunger__ - hodnota mezi 0 - 100 určuje uroveň hladu
- __Housing__ - ukladá zda má jedinec kde bydlet
- __Work__ - ukládá typ práce, kterou daný jedinec zrovna provozuje

#### Happiness

__Štěstí__ bude ovlivněno __Hladem__, __Prací__ a __Ubytováním__. Pokud hlad klesne pod 70% stěstí začne klesat. Na 20% se spustí hladovění.

## Suroviny

1. Základní:
   - Jídlo
   - Dřevo
   - Kamení
2. Pokročilé
    - Nástroje
    - Plaňky
    - Kamené cihly
3. Pokročilé spracování jídla:
    - Obilí
    - Mouka

### Přehled surovin

| Typ suroviny | Počáteční hodnota | Počáteční kapacita | Popis |
| --- | --- | --- | --- |
| Bydlení | 0 | 0 | Bydlení poskytuje populaci možnost se ubytovat, každý jedinec zabírá 1 místo.
| Jídlo | 20 | 250 | Jídlo pro populaci |
| Dřevo | 0 | 250 | Surové dřevo |
| Kamení | 0 | 250 | Surové kamení |
| Nástroje | 0 | 100 | Nástoroje umožnují provádění efektivnější práce |
| Plaňky | 0 | 100 | Pokročilý materiál |
| Kamené cihly | 0 | 100 | Pokročilý materiál |
| Obilí | 0 | 60 | Pokročilé spracování jídla |
| Mouka | 0 | 60 | Pokročilé spracování jídla |

## Práce

Každý __jedinec__ může provozovat __1 práci__, která je poskitnuta odpovídající __budovou__. Práce může brát několik různých surovin jako vstup a poskitovat 1 novou surovinu jako výstup.

Na začátku hry jsou poskitnuty 3 základní prace:

- __Sběrač Jídla__
- __Sběrač Dřeva__
- __Sběrač Kamení__

Tyto práce nevyžadují žádnou vstupní surovinu a počet pracovníků není oezen.

### Přehled prací

| Typ Práce | Výstup | Vstup | Popis |
| --- | --- | --- | --- |
| Sběrač jídla | 0.022 __Jídla__ | / | Základní sběr jídla |
| Sběrač dřeva | 0.05 __Dřeva__ | / |  Základní sběr dřeva |
| Sberač kamení | 0.01 __Kamení__ | / | Základní sběr kamení |
| Nástrojář | 0.01 __Nástrojů__ | 0.08 __Dřeva__ 0.04 __Kamení__ | Jednoduchá výroba nástrojů |
| Dřevorubec | 0.2 __Dřeva__ | 0.05 __Nástrojů__ | Lepší produkce dřeva |
| Kamenolomec | 0.15 __Kamení__ | 0.08 __Nástrojů__ | Lepší produkce kamení |
| Lovec | 0.04 __Jídla__ | 0.05 __Nástrojů__ | Lepší produkce jídla |
| Truhlář | 0.05 __Planěk__ | 0.02 __Nástrojů__ | Pokročilý materiál |
| Kameník | 0.05 __Kamených cihel__ | 0.04 __Nástrojů__ | Pokočilý materiál |
| Farmář | 0.08 __Obilí__ | 0.03 __Nástrojů__ | Pokročilá produkce jídla |
| Mlynář | 0.3 __Mouky__ | 0.5 __Obilí__ |  Pokročilá produkce jídla |
| Pekař | 0.25 __Jídla__ | 0.1 __Mouky__ | Pokročilá produkce jídla |

## Budovy

Budov je možné postavit  neomezené množství.

### Přehled budov

| Typ budovy | Efekt | Cena |
| --- | --- | --- |
| Sklad | zvýší kapacitu surovin o její počáteční hodnotu | |
| Dům | +4 místa na __Bydlení__ | |
| Nástrojářská chatka | +1 práce __Nástrojář__ |
| Dřevorubecká chata | +2 práce __Dřevorubec__ |
| Kamenolom | +2 práce __Kamenolomec__ |
| Lovecká chata | +3 práce __Lovec__ |
| Kamenická dílna | +2 práce __Kameník__ |
| Dřevařská dílna | +3 práce __Tesař__ |
| Farma | +6 práce __Farmář__ |
| Mlýn | +3 práce __Mlynář__ |
| Pekárna | +2 práce __Pekař__ |
