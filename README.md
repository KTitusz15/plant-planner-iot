# Dinamikus szobanövény-monitorozó rendszer hardveres és AI technológiával

A szakdolgozat célja egy komplex, felhőalapú webalkalmazás fejlesztése, amely modern webes technológiákat ötvöz IoT és gépi tanulási elemekkel. 

## Projekt információk
* **Hallgató:** Királyházi Titusz (Neptun-kód: X5Q04E)
* **Szak:** Programtervező informatikus BSc, nappali
* **Témavezető:** Jász Judit Dr. egyetemi docens (Szoftverfejlesztés Tanszék)

## A rendszer fő funkciói
1. **Növénynapló:** Növények böngészése a Perenual API adatbázisára támaszkodva, és saját virtuális naplóhoz adásuk az ideális gondozási paraméterekkel.
2. **Környezeti monitorozás:** A fizikai szenzoroktól érkező adatok (hőmérséklet, páratartalom, fényerő és talajnedvesség) valós idejű fogadása és grafikonos megjelenítése.
3. **Kontextusfüggő riasztások:** A Perenual API által meghatározott elvárt értékek összevetése a szenzorok valós mérési adataival, kritikus eltérés esetén proaktív e-mail értesítés küldése és a teendők jelzése a webalkalmazás felületén.
4. **Betegségdiagnosztika:** AI-alapú kártevő- és betegségazonosítás a Plant.id API segítségével, a feltöltött fotó és az elmúlt időszak szenzoros adatainak együttes elemzésével.

## Technológiai Stack
* **Frontend:** React (Next.js)
* **Backend:** Node.js (Next.js API Routes, Vercel Serverless architektúra)
* **Adatbázis:** MongoDB Atlas (NoSQL)
* **Hardver (IoT):** ESP32 mikrokontroller, DHT22 (hő- és páratartalom), BH1750 (fényerő), SOILCAP-V20 (kapacitív talajnedvesség érzékelő)
* **Nyelvek:** TypeScript, C++
