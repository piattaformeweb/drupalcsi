# CMS Drupal 7 per i siti web dei comuni

Documento aggiornato al 12/04/2017

## Fornitore

CSI Piemonte, C.so Unione Sovietica, 216 - 10134, Torino

[piattaformeweb@csi.it](mailto:piattaformeweb@csi.it)

## Responsabile del progetto

Andrea Muraca
 [andrea.muraca@csi.it](mailto:andrea.muraca@csi.it)

## Riferimenti tecnici del progetto

Carlo Sacripante
 [carlo.sacripante@csi.it](mailto:carlo.sacripante@csi.it)

Andrea Di Pizio
 [andrea.dipizio@csi.it](mailto:andrea.dipiio@csi.it)

## Licenza

Il pacchetto è rilasciato con [licenza GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html)

All&#39;interno del pacchetto, vedi file:

- COPYRIGHT\_CMS.txt
- LICENSE\_CMS.txt

## Linguaggi e framework utilizzati

Drupal 7.5x su stack LAMP (Linux CentOS, Apache 2.2.x, MySQL 5.6.x, PHP 5.6.x)

## Librerie incluse

Le seguenti librerie o componenti sono già incluse nel pacchetto distribuito:

**Framework CSS:** Bootstrap 3.3.x

**Font:** Font Titillium Web, Font Awesome 4.7.x

**Framework JS** : JQuery 1.x (fornito con Drupal)

**Plugin JS:** CKEditor 4.5.x, JQuery Easing 1.3, JPushMenu 1.1.1, JQuery Navgoco 0.2.1, OwlCarousel2, Packery 2.1.1 (open source), Venobox, JQuery matchHeight, JQuery ScrollTo 2.1.2, QTip2 3.0.3, FitVids.js, iScroll, Modernizr 2.6.2, Html5Shiv 3.7.3, Respond 1.4.2, Plupload 1.5.8, Masonry.

## Requisiti di sistema per l&#39;hosting

**Requisiti minimi:** vedi i requiisiti per l&#39;installazione di Drupal 7 [https://www.drupal.org/docs/7/system-requirements](https://www.drupal.org/docs/7/system-requirements)

**Requisiti ulteriori consigliati:**

- PHP &gt;= 5.6.x
- PHP cURL installato
- OPcache attivo, Memcache attivo (memcache richiede un modulo e configurazione aggiuntiva)
- memory\_limit = 128Mb
- max\_execution\_time = 60
- post\_max\_size = 64Mb
- upload\_max\_filesize = 20Mb

Per effettuare il login in [modalità sicura](https://www.drupal.org/https-information) è stato utilizzato il modulo contrib _securelogin_ configurato sullo stesso dominio. Pertanto è richiesto che il virtual host sia configurato per accettare connessioni http/https, in particolare https per le connessioni autenticate, http per quelle anonime (no &quot;mixed mode&quot;). Una volta completato il processo di installazione occorre abilitare il modulo in _admin/modules_.

Per il funzionamento del modulo Twitter si richiede che il virtual host sia raggiungibile dall&#39;esterno, cioè non sia &quot;mascherato&quot; da eventuali proxy, firewall o altri apparati di rete. Una volta completata l&#39;installazione occorre aggiungere un account autenticato in _admin/config/services/twitter_.

## Requisiti del client

**Desktop:** Sono supportate tutte le versioni recenti di Google Chrome, Safari e Firefox. E&#39; supportato Internet Explorer dalla versione 9 in poi: IE 8 è supportato ma non garantisce la stessa user experience delle versioni successive.

**Mobile:** sono state testate tutte le versioni standard dei browser, cioè quelle di default per i vari dispositivi (si riporta la [tabella relativa](http://getbootstrap.com/getting-started/#support) dal sito di Bootstrap).


|   | **Chrome** | **Firefox** | **Safari** |
| --- | --- | --- | --- |
| **Android** | Supported | Supported | N/A |
| **iOS** | Supported | Supported | Supported |


## Eventuali procedure schedulate (cron) e loro funzionamento

E&#39; raccomandato l&#39;utilizzo di un cron esterno con cadenza regolare (ad esempio ogni 4 ore) che richiami l&#39;url del cron di Drupal, in modo da non creare rallentamenti nella navigazione degli utenti.

## Struttura database

Non sono presenti tabelle custom.

## Tipologie di contenuto

Questi i content type realizzati con Drupal 7:

- **Articolo**
Usato per pubblicare news con una data di pubblicazione. Le singole news possono essere legate alla tassonomia delle aree tematiche.
- **Evento**
Usato per pubblicare eventi ed appuntamenti anche geolocalizzati che hanno una durata (data di inizio e data di fine evento).
- **Galleria immagini**
Usato per raccogliere foto ed illustrazioni in album sfogliabili.
- **Pagina informativa**
Usato per tutte le pagine statiche di tipo informativo.
- **Scheda personale**
Usato per le schede individuali, ad esempio per inserire i dati relativi ai membri degli organi di governo comunali.
- **Struttura organizzativa**
Usato per realizzare le schede di settori, aree, servizi o uffici comunali.
- **Webform**
Usato per creare moduli interattivi, come sondaggi, form di contatto etc.

## Manuale di installazione


### Installazione manuale

1. Scaricare l&#39;archivio compresso .zip
2. Scompattarlo nella cartella di destinazione
3. Scompattare e caricare lo schema db.sql.zip sul DB
4. Duplicare il file /sites/default/default.settings.php in settings.php
5. Modificare le impostazioni relative al DB nel file /sites/default/settings.php
6. Loggarsi sul sistema come _admin/P@ssw0rd!_ e modificare le impostazioni del filesystem all'url /admin/config/media/file-system in particolare configurando la cartella dei file pubblici, quella dei file privati e quella temporanea.
7. Consultare la pagina /admin/reports/status per eventuali anomalie

### Installazione via Git
1. Clonare il repository
2. Seguire le istruzioni precedenti dal punto 3 in poi

### Installazione da archivio Drush

1. Scaricare il file site.tar.gz e posizionarlo nella cartella di destinazione
2. Posizionarsi nella stessa cartella
3. Eseguire il comando seguente inserendo i parametri del DB


`drush archive-restore site.tar.gz --db-url=mysql://user:password@ip-address/dbname`

1. Loggarsi sul sistema come _admin  P@ssw0rd!_ e modificare le impostazioni del filesystem in /admin/config/media/file-system in particolare configurando la cartella dei file pubblici, quella dei file privati e quella temporanea.
2. Consultare la pagina /admin/reports/status per eventuali anomalie

## Configurazione del sistema

Una volta installato il sistema occorre apportare le seguenti modifiche:

1. Apportare le necessarie modifiche al file _.htaccess_ presente nella root del sito, in particolare, se il sito è installato in una sottocartella, configurare la _RewriteBase_
2. Accedere alla pagina _admin/config/media/file-system_ e configurare le cartelle private e pubbliche specialmente la cartella temporanea che deve essere scrivibile da parte del webserver;
3. Accedere alla pagina _admin/config/system/site-information_ per configurare il nome del sito, ed altri parametri;
4. Accedere alla pagina _admin/appearance/settings/agid_ per impostare il percorso del file del logo;
5. (facoltativo) Modificare i colori del sito nei file SCSS del tema (sites/default/themes/agid/scss) e rigenerare i CSS con un compilatore SASS (vedi file _\_drupal-boostrap-variables.scss_ e _\_variables.scss_);
6. (facoltativo) Ottimizzare la configurazione SEO per i motori di ricerca
  1. modificando il file _robots.txt_ (posizionarlo nella root del dominio)
  2. abilitando e configurando il modulo _sitemapxml_
  3. abilitando e configurando il modulo _metatag_
7. (facoltativo) Abilitare i sistemi di cache e di compressione delle risorse statiche;
8. (facoltativo) Abilitare eventuali moduli aggiuntivi (_securelogin_, _twitter_, etc.).

## Aggiornamenti

Il sistema è stato concepito per essere aggiornato con le modalità canoniche di Drupal, quindi attraverso il modulo _Update manager_ oppure via _drush_. Il core è aggiornabile solo manualmente.

## Manuale d&#39;uso Drupal 7

Vedi [https://www.drupal.org/docs/7](https://www.drupal.org/docs/7)

## Eventuali modifiche al core e ai moduli (allegando patch)

Non sono state apportate modifiche al core.

Sono state apportate le seguenti patch a moduli contrib:

**l10\_update**

[https://www.drupal.org/node/750000#comment-11372545](https://www.drupal.org/node/750000#comment-11372545)

[https://www.drupal.org/files/issues/l10n\_update-allow-alternate-http-client-750000-15.patch](https://www.drupal.org/files/issues/l10n_update-allow-alternate-http-client-750000-15.patch)

**block\_attributes**

[https://www.drupal.org/node/2800761#comment-11627501](https://www.drupal.org/node/2800761#comment-11627501)

[https://www.drupal.org/files/issues/classtocontent-2800761-1.patch](https://www.drupal.org/files/issues/classtocontent-2800761-1.patch)

## Moduli custom

E&#39; stato sviluppato il modulo custom _share\_button_ che permette di condividere una pagina sui circuiti social. Il modulo non è stato ancora rilasciato alla community e fa parte esclusivamente di questa distribuzione.
