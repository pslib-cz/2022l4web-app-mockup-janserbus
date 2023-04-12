# Web based RPG/strategie

Hráč bude spravovat vesnici, rozrůstat jí, sbýrat nové suroviny

## Začátek hry

Hra začíná se 12 lidmi a s 250 jednotkami potravin. Hráč bude přiřazovat volné lidi do práce, čímž bude generovat suroviny. Ze začaáku hry se bude jednat především o jednoduché suroviny a práce. Sběrači budou produkovat malé možství jídla, což bude znamenat, že pro uživení populace bude nezbytné aby většína lidí sbírala jídlo. Zbylích pár jedniců pak bude moci sbírat dřevo nebo kamení.

## Globální proměnné

1. rok = 40s - doporučené nastavení
2. populačníRůst = 0.05%/rok

## Zdroje

1. základní
   - Pracovní síla - využívá se k získání ostatních zdrojů
   - Dřevo - stavební materiál
   - Potraviny - nezbytné pro růst populace
2. Pokročilé zdroje:
   - Kámen

## Populace (Pracovvní síla)

Růst populace bude modelován pomocí nasledující rovnice: $P = P_0*e^{rt}$

### Třída jedinec

- Happiness - hodnota mezi 0 - 100 určuje jak moc je jedinec šťastný
- Hunger - hodnota mezi 0 - 100 určuje uroveň hladu
- Work - ukládá typ práce, kterou daný jedinec zrovna provozuje
- eat() - stará se o stav hladu daného jedince
- work() - vyprodukuje suroviny v závislozti na páci

#### Happiness

Štěstí bude ovlivněno __Hladem__ a __Prací__. Pokud hlad klesne pod 70% stěstí začne klesat. Na 20% se spustí hladovění

## Suroviny

Speciální mechanika regulující jejich dostupnost

### Dřevo



### Kámen

## Budovy
