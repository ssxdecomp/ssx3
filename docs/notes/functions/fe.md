<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/fe/

## `src/fe/debugfe.cpp`

Segment `0x0017C5F8`-`0x00180B60`.

- **`0x0017FDF0`** - First FEUIInput method (vtable `0x0046D1D0`). *[static]*

## `src/fe/festatedebug.cpp`

Segment `0x00180B60`-`0x00181148`.

- **`0x00181090`** - cFEStateCharSelect (`08sel_char`) code; plays no game-code sound, since a rider change is a UIMenu cursor move (kind 1). *[static]*

## `src/fe/festatecharselect.cpp`

Segment `0x00181148`-`0x00182928`.

- **`0x00181620`** `cFEStateCharSelect_onWidgetCreate` - Select Character runtime field fill (rider names and related texts); works with the stats fill `0x00181BD0`. *[static]*
- **`0x001817E8`** - Contains the Select Character Cross handling that requests the Post_Selection speech. *[static]*
  - `0x0018185C`: Select Character Cross: sets FE preview slot `+0xC20` (Post_Selection speech request). *[static]*
- **`0x00181BD0`** - Select Character stats fill: reads raw bytes at `0x00535538` + player*70 + char*7 and shows seven attributes as raw*0.2 ('%.1f') with bar raw/55. NumAttr0..6 = Acceleration, Edging, Speed, Spin, Stability, Toughness, Tricks come from bytes 1,3,0,4,6,5,2. Rider ranking = (sum - sum%5)/35, ranking bar sum/7. A fresh profile has every raw value 5, so every stat shows 1.0. *[static]*
- **`0x00181EF0`** - Select Character 3D preview placement: camera eye (0,200,0) looking at the origin, 25 deg half-horizontal; rider root at (136,-250,-82) cm turned 100 deg, unscaled (preview geometry `+0x140` = 1.0); board moved out of view; the right stick turns the rider 3 deg per frame. *[PS2]*
- **`0x00182220`** - cFEStateCheatCharSelect code: the Cheat Characters list screen (`131cheat_char`), opened from Setup Character > Rider Details. Shows the base rider's face first, then owned cheat characters in id order, in six face slots with the focused face enlarged and a name bar; picking one puts that skin on the current base rider. *[static]*
- **`0x00182808`** - CheatCharSelect input query: Cross plays sound 3 only. *[static]*

## `src/fe/festatecharsetup.cpp`

Segment `0x00182928`-`0x001832A8`.

- **`0x00182928`** `cFEStateCharSetup_onCreateScreen` - Sets up the Setup Character screen (`09set_char`): Continue, Equip Gear, Rider Details, Music, with all four items enabled and Option_GBA hidden. *[static]*
  - `0x0018293C`: Setup Character screen setup block: widgets Option_Continue/_Equip/_Rider/_Radio = 0..3, Option_GBA hidden. Continue goes to Select Peak; Square opens FEOptions (handled at `0x00182D58`). *[static]*
  - `0x00182AA8`: Start of the item-enable calls (`0x00182AA8`..`0x00182BD8`); all four items are enabled. *[static]*
- **`0x00182C68`** - RiderDetail / CharSetup input query: Cross, Triangle and Square play sound 3. *[static]*
- **`0x00182C80`** - Contains the Setup Character Square handling that opens FEOptions. *[static]*
  - `0x00182D58`: Setup Character: Square opens FEOptions. *[static]*

## `src/fe/festateriderbio.cpp`

Segment `0x001832A8`-`0x00183DE0`.

- **`0x001832A8`** `cFEStateRiderDetail_onCreateScreen` - Sets up the Rider Details screen (`154rider_details`): Rewards, Cheat Characters, Ubertrick Setup, Player Name, Rider Profile. *[static]*
  - `0x001832BC`: Rider Details screen setup block: widgets Option_1..5 = 5..9. Cheat Characters is disabled when `0x001577A0` returns 0 (`0x00183550`); Square opens FEOptions (`0x00183A2C`); Player Name handled at `0x00183764`. *[static]*
- **`0x00183550`** - Disables the Rider Details Cheat Characters item through `0x00194498` when `0x001577A0` returns 0. *[static]*
- **`0x00183710`** - Contains the Rider Details Player Name and Square (FEOptions) handling below. *[static]*
  - `0x00183764`: Player Name: opens cKeyboardPopup with the current name (fresh name PLAYER1), focus on Done, max 15 chars; Tab and punctuation keys disabled by ten `0x001CE3C8` calls (Up/Down always dim). A non-empty name is stored via `0x00147138`. *[static]*
  - `0x00183A2C`: Rider Details: Square opens FEOptions. *[static]*
- **`0x00183A98`** - cFEStateUberTrick (trick shop) state code. *[static]*

## `src/fe/festatestore.cpp`

Segment `0x00184668`-`0x00185A98`.

- **`0x001849B0`** - Sets up the Ubertrick Setup screen (`66ut_btnmap`, cFEStateUberTrick): grab categories with their uber lists, and the preview camera. *[PS2]*
  - `0x001849C4`: Ubertrick Setup screen block: categories Mute, Indy, Stalefish, Method, Nose Grab, Tail Grab, DONE, then the category's ubers (check = selected, box = owned, $ = locked). The list opens on its first row and wraps. *[static]*
  - `0x00184A78`: Ubertrick preview camera: eye (0,660,80) -> target (0,0,80), 25 degrees. *[PS2]*
- **`0x00184C60`** - Ubertrick Setup trick preview (vtable `0x0046CCC8`, state `66ut_btnmap`): rider on the board in the FE preview slot looping FE_A_CYC (436). Square plays the focused uber: sets the animator semantic to the uber's trick id with the FE variant from the runtime table *(`0x004A3DFC`, gp+0xD0C), plays once, then crossfades back (0.23 s). Root at (-228,-205,63) cm turned 62 deg about Z; no `0x0019F548` board move. *[PS2]*
  - `0x00184D08`: Preview root placement: (-228,-205,63) cm turned 62 deg about Z using the 31 deg half-angle at `0x0049D700` (gp-0x59F0). *[PS2]*
- **`0x00184F40`** - Lodge Uber purchase; calls `0x0014FE08`. *[static]*
- **`0x00185268`** - Contains the trick shop (cFEStateUberTrick) Cross purchase check below. *[static]*
  - `0x00185528`: Trick shop Cross: error sound (kind 4) when cash (`0x00150928`) < price, else opens the 'UITRICKBUY' popup. *[static]*
- **`0x001859D8`** - UberTrick input query: Cross and Triangle play sound 3. *[static]*

## `src/fe/festatecredits.cpp`

Segment `0x00185A98`-`0x00186658`.

- **`0x00185A98`** `cFEStateCredits_onCreateScreen` - Sets up the credits screen (`26credits`, cFEOptionsCredits): the kT_CREDITS roll from CRAMER.LOC. *[static]*
- **`0x00185BA0`** `cFEStateCredits_onGainFocus` - Builds the credits roll: the 160 kT_CREDITS lines in a fixed order, scrolling up 1 px per frame inside the TextScroll box, with the Dolby bitmaps after the text. *[static]*
  - `0x00185C54`: Start of the credits text list (`0x00185C54`..`0x00185F04`) giving the order of the 160 kT_CREDITS lines; a backslash breaks a line, '^' marks a heading. *[static]*
- **`0x00186478`** - Credits input query: Triangle plays sound 3 only. *[static]*
- **`0x00186610`** - cFEStateEventSelect item events: forwards to the EventSelect logic `0x002018A8`. *[static]*

## `src/fe/festateload.cpp`

Segment `0x00186658`-`0x00186B50`.

- **`0x00186950`** - EventSelect input query: returns 0x101 unless `0x00202738(state+0x48)` says the event-select logic owns input, then 0. *[static]*

## `src/fe/festatelegal.cpp`

Segment `0x00187C50`-`0x00188800`.

- **`0x00187D38`** - Enter Cheat code check: lowercases the typed text, hashes it with `0x00317670` and unlocks the matching cheat character for all ten riders of profile 0; returns 1 for a valid code. Codes: zenmaster Brodi, worm Eddie, bronco Luther, back2future Marty, slicksuit Hiro, brokenleg Jurgen, notsosvelte Svelte Luther, windmilldunk Stretch, milkemdaisy Cudmore, wheresyourtail Bunny San, tankengine Churchill, boneyardreject Gutless, betyouveneverseen Snowballs, callhimgeorge NW Legend, finallymadeitin Unknown Rider. The song cheat owns every song; there is no all-characters code. *[static]*
- **`0x001887A0`** - cFEStateOptions: FEOptions (`18options`) screen code, including the Enter Cheat keyboard handling. Items Game Options, Sound Options, Controller Settings, HUD Options, Save/Load, Enter Cheat, Credits, DONE, all enabled (no enable calls); leaving asks to save the Options with the FE.LUI popup. *[static]*

## `src/fe/festateoptions.cpp`

Segment `0x00188800`-`0x0018EAD8`.

- **`0x00188980`** - Contains the cFEStateOptions Enter Cheat keyboard-close handling: accept or error sound depending on the cheat check `0x00187D38`. *[static]*
  - `0x00188BF0`: Enter Cheat keyboard closes: sound kind 6 if `0x00187D38` returns 1 (valid code), else kind 4 (`0x00188C28`). *[static]*
  - `0x00188C28`: Invalid cheat code: plays kind 4 (error). *[static]*
- **`0x00188C68`** - Options input query: Cross and Triangle play sound 3. *[static]*
- **`0x00189958`** - OptionsGame input query: Cross, Triangle and Square play sound 3. *[static]*
- **`0x00189980`** `cFEStateOptionsGame_onWidgetEvent` - Contains the Game Options store of the widescreen setting, followed by a call to `0x00228C08`. *[PS2]*
  - `0x00189D14`: Front-end Options menu store of the widescreen setting. *[PS2]*
  - `0x00189D34`: Call to `0x00228C08` after the widescreen setting store. *[PS2]*
- **`0x0018A258`** - cFEStateOptionsSound: Sound Options screen (`141advsettings`) code; works with `0x0018B380`. *[static]*
- **`0x0018A890`** - OptionsSound input query: Cross silent, Triangle and Square play sound 3. *[static]*
- **`0x0018B380`** `cFEStateOptionsSound_updateWidget` - Sound Options screen routine, listed with cFEStateOptionsSound `0x0018A258`. *[static]*
- **`0x0018BEF8`** - Calls the front-end audio init `0x00285FB0`. *[static]*
- **`0x0018C270`** - OptionsHUD input query: Cross silent, Triangle and Square play sound 3. *[static]*
- **`0x0018CCE0`** - OptionsController input query: Cross silent, Triangle and Square play sound 3. *[static]*

## `src/fe/festateprofile.cpp`

Segment `0x0018EAD8`-`0x001908C0`.

- **`0x0018EDC8`** `cFEStateProfileLoad_onCreateScreen` - Sets up the profile Load screen (`93profile_load`, cFEStateProfileLoad): a load game list with rows 1..6 (player%d, date%d, time%d). *[static]*

## `src/fe/festateriderbiodetail.cpp`

Segment `0x001908C0`-`0x001913B8`.

- **`0x001908C0`** `cFEStateRiderBio_onCreateScreen` - Rider Profile screen (`14rid_prof`) code: pages Rider DNA / Faves / Q&A / BIO, opening on Rider DNA. Left/Right cycle pages with wrap and flash the arrow (Down/R1/L1 do nothing); one page's groups are shown and the others hidden. Texts kT_DNA1..8, kT_FAVES1..12, kT_QNA1..4, kT_FULLBIO1 + first name. *[static]*

## `src/fe/festatebigradio.cpp`

Segment `0x00192D80`-`0x00194528`.

- **`0x00193CF8`** - BraggingRights state code (input query not evaluated: jump tables). *[static]*
- **`0x00194138`** - Contains a call to the online message pump `0x001A8B88`. *[static]*
  - `0x00194154`: Call to the online message pump `0x001A8B88`. *[static]*
- **`0x00194498`** - Disables an FE menu item: it is drawn at alpha 96 and skipped by Up/Down focus. Used for Rider Details' Cheat Characters (via `0x00183550`) and Main Menu Multi Play. *[static]*

## `src/fe/festatetransition.cpp`

Segment `0x00194528`-`0x00194778`.

- **`0x001946A8`** - cFEStateTransition: FE screen-change transition page (vfunc `+0xC0`); arg 0 plays UI sound ev 15 (snd 7), arg 1 is the silent whitefade. Driven from `0x001A0830` case 0. *[static]*
  - `0x001946E4`: Transition page start: UI sound ev 15 (snd 7). *[static]*

## `src/fe/ovstates.cpp`

Segment `0x00194778`-`0x001954D8`.

- **`0x001948A8`** - Title screen idle state code: plays the intro movie. *[static]*
- **`0x00194988`** - cFEStateTitle code: sets kind[0] = 0 on the 'Press START' item via `0x003A0330(tReal, 0, 0)`. *[static]*
- **`0x00194A48`** - cFEStateTitle input query: returns 0x101 for Cross/Start (ev 6 -> accept sound 3), nothing else. *[static]*
- **`0x001952E8`** - MainMenu input query: Cross, Triangle and Square play sound 3. *[static]*

## `src/fe/festatebonusmaterial.cpp`

Segment `0x001954D8`-`0x001956F8`.

- **`0x00195600`** - cFEStateBonusMaterial input handler (`146Bonusmat` Previews): plays the NFS Underground, NFL STREET and NBA STREET Vol. 2 trailers. *[static]*

## `src/fe/festateaudiooptions.cpp`

Segment `0x00196540`-`0x00196F98`.

- **`0x00196540`** `cFEStateAudioOptions_onWidgetCreate` - Audio options widget create: sets the radio item values (`+0x18`): 'radio big' 0, 'big mountain' 2, 'request line' 1, 'playlist' 3, 'edit req' 4. *[static]*
- **`0x001966E0`** `cFEStateAudioOptions_onWidgetEvent` - Audio options widget events; Cross on a radio mode moves the check sprites, saves the mode and applies it immediately. *[static]*
  - `0x00196770`: Cross-on-a-mode block: moves the check sprites, saves the mode (`0x001587F8`) and calls SetRadioMode `0x0028BF78` immediately. *[static]*
- **`0x00196B08`** - cFEStateAudioOptions input query: Cross returns 0x10 (error sound) for unavailable radio items (index 2..4), else 0x101; Square/Circle return 0. *[static]*
- **`0x00196B90`** - cFEStateRequestLine: Request Line / Edit Playlist screen (`16radio` in the FE, `143radio_pda` in game). Highlighting a song sends its PREVIEW to charsel in the FE or plays it at once in game; exit saves the masks, calls `0x0028C2D0` and sends event 10 if a preview ran (CTM flag). *[static]*

## `src/fe/messagecenter.cpp`

Segment `0x00196F98`-`0x00198DB8`.

- **`0x00197500`** - Contains the Request Line exit (Triangle) handling: saves the playlist masks and returns to Music. *[static]*
  - `0x0019768C`: Request Line Triangle (event 6): saves both masks (`0x00158848` / `0x00158820`), calls `0x0028C2D0`, returns to Music with Edit Playlist focused. *[static]*
  - `0x001976E0`: Request Line exit sends charsel event 10 only with the CTM flag. *[static]*
- **`0x001977D0`** - cFEStateRequestLine input query: Cross plays sound 3 or the error sound (0x10); Triangle and Square sound 3; Circle 0. *[static]*
  - `0x00197910`: Square = Preview (query 8): in the FE calls the `0x002B4978` preview; in game, owned songs only set audio `+0x508` and call PlayMusic(0, 0, -1, 1). *[static]*
- **`0x00197AD8`** - Request Line song list: 35 songs (audio `+0x504`), owned first then the rest in song order; 8 rows with arr_up / arr_down. *[static]*
- **`0x00197CA0`** - Request Line song boxes: in playlist -> checkbox; owned -> empty box; not owned -> yellow dollar. *[static]*
- **`0x00197E70`** - Request Line in game: sets the 'Now playing: %S' / 'Artist: %S' labels for the current song. *[static]*
- **`0x00198118`** - Request Line text 'Songs in your playlist:  %d'. *[static]*
- **`0x00198340`** `cFEStateRequestLine_updateButtonsText` - Request Line Cross label: Remove song / Add song / Buy song, or hidden. *[static]*
- **`0x001986D0`** `cFEStateRequestLine_updateHilightedSongInfo` - Request Line text 'Song by:  %S' for the focused song. *[static]*
- **`0x001988D8`** - Song buy popup 'Yes' handler: buys the song through `0x00158558`. *[static]*
- **`0x00198988`** - Opens cUIStateBuyPopup for an unowned song. *[static]*
- **`0x00198AE8`** - Song price: a free credit while fewer than 6 songs are owned, else $5,000. *[static]*

## `src/fe/festatecharequipdetail.cpp`

Segment `0x00198DB8`-`0x0019E680`.

- **`0x00199A38`** - Contains the Equip Gear preview right-stick handling: stick X turns the rider, stick Y zooms. *[PS2]*
  - `0x00199AAC`: Equip Gear right stick X: turns the rider +3 degrees per frame. *[PS2]*
  - `0x00199B64`: Equip Gear right stick Y: zoom z += -0.1 * stick, clamped to [0,1]. *[PS2]*
- **`0x00199C28`** - Contains Equip Gear item handling: Boards folder view-state changes, the gear weight limit check and the commit speech request. *[static]*
  - `0x00199D14`: Entering the Boards folder sets the Equip Gear view state to 3 (ease to board view). *[static]*
  - `0x00199D30`: Weight-limit check block: refuses an equip when the limit *(`0x004A18D8`, gp-0x1818) (3392) < current weight + change. *[static]*
  - `0x00199E30`: Leaving the Boards folder sets the Equip Gear view state to 4 (ease back). *[static]*
  - `0x00199EA4`: Equip Gear commit sets FE preview slot `+0xC1C` (Customize speech request). *[static]*
- **`0x00199F20`** - CharEquip state code (input query not evaluated: jump tables). *[static]*
- **`0x0019AFD0`** - Tests whether a gear folder holds an owned listed item; used by the Equip Gear list builder `0x0019B180`. *[static]*
- **`0x0019B098`** - Buy Gear list builder, together with `0x0019B180`. *[static]*
- **`0x0019B180`** - Builds the Equip Gear list: named owned leaves plus folders holding one (tested by `0x0019AFD0`); children come from `0x0014D7E8`, sorted by `+0xA`. Only owned items appear (a fresh Zoe lists 2 hairstyles, 1 eyewear, 3 tops, 3 hands, 2 bottoms, 1 boots, 1 board). Also part of the Buy Gear list building with `0x0019B098`. *[PS2]*
- **`0x0019B7E0`** - Contains a block that precomputes an equip's weight change by simulating `0x0014AFB0`. *[static]*
  - `0x0019B8F0`: Weight-change precompute block: simulates `0x0014AFB0` to get an equip's weight change. *[static]*
- **`0x0019BC90`** - Equip Gear bar 1 ('Your current outfit'): fill = (w - 1500) / (3392 - 1500). *[static]*
- **`0x0019BD48`** - Equip Gear bar 2 ('Your possible outfit'): fill = (w - 1500) / (3392 - 1500). *[static]*
- **`0x0019BEE8`** - Equip Gear Cross: toggles the item by its committed bit (on = !(flags & 4)), then commits via `0x0014AEA8`. *[PS2]*
- **`0x0019BFE8`** - Equip Gear preview update: places the FE preview rider/board with rider and board views and easing. Rider at (-105, -100+320z, -80-65z) turned qZ(`+0xAAC` + 80 deg); board view (-250,-650,-215). Easing p += (target-p)*0.2 until squared distance < 0.2. Stick X turns +3 deg/frame (`0x00199AAC`), stick Y zoom z += -0.1*stick clamped to [0,1] (`0x00199B64`). The rider updates as soon as an item is equipped. *[PS2]*

## `src/fe/feridermanager.cpp`

Segment `0x0019E680`-`0x001A0648`.

- **`0x0019EE88`** - FE preview lighting, used when slot `+0xCD4` < 0: builds the rider's IRR lighting bank and copies it to the renderer. `0x00389260` clears the bank, `0x00389590` adds the IRR.DAT record (weight 1.0, modulation 1,1,1,1), `0x00389CB8(bank, hips world pos from 0x00310C48, 1.0)` evaluates it with the FE camera view (block `+0x40`), then renderer vtable `+0x22C` (`0x003954D0`) copies it to renderer `+0x6BB0`. Record ids: 0 moby, 1 kaori, 2 allegra, 3 mac, 4 zoe, 5 griff, 6..8 elise, 9 viggo, >=10 fe_map. No env bank or local lights. *[PS2]*
- **`0x0019F548`** - Places the FE preview board (slot `+0xC50` position / `+0xC60` quaternion); moves it out of view on Select Character. Equip Gear: board at (265.75,-1073.5,-232), or (-100,45,15) in the board view; q = rotZ(2*2.138029) rotY(2*2.792527) rotX(spin+90 deg), spin +1 deg/frame mod 360. Not called by the Ubertrick preview. *[PS2]*
- **`0x001A0358`** - Front-end rider preview speech: polls the FE preview slot speech flags on Setup Character / Equip Gear. `+0xC20` -> `0x002A16B0` Post_Selection (0x20BC) only when `0x00535C11` != 0; `+0xC1C` -> `0x002A1778` Customize (0x20BD) in every mode. Plays on the CHARACTER bus with the slot's character (a skin's base rider). *[static]*

## `src/fe/fereal.cpp`

Segment `0x001A0720`-`0x001A3090`.

- **`0x001A0720`** `cFECustom_cFECustom` - CTM free-ride start: a new career starts at Happiness (14), dropped from the plane; later starts use the last lodge (profile `+0x27C`, 17 at first). *[static]*
  - Possible mismatch with the current name: The decomp name marks this as the cFECustom constructor, but the records describe it only as the CTM free-ride start-location selection.
- **`0x001A0830`** `cFECustom_getNextState` - FE screen-flow routine: chooses the next screen and drives the transition page (case 0). *[static]*
  - `0x001A1360`: Lodge -> Music opens the audio options with flag 1. *[static]*
- **`0x001A16C0`** - Contains FE screen-flow handling for Setup Character -> Music in the career flow. *[static]*
  - `0x001A181C`: Setup Character -> Music opens the audio options with the CTM flag (career flow). *[static]*
- **`0x001A1CE8`** - Front-end boot: plays the EA/THX boot movies and calls the front-end audio init `0x00285FB0`. *[static]*
- **`0x001A1EC0`** `cRealFE_load` - Contains a front-end transition call to `0x0014AF10`, which drops uncommitted gear changes. *[static]*
  - `0x001A1F1C`: Call to `0x0014AF10` (drops uncommitted gear changes) on a front-end transition. *[static]*
- **`0x001A2E58`** - FE UI sound listener 'FEUISound' (vtable `0x00469348`): UI sound kinds 1..6 map to events 2, 3, 1, 4, 0, 0. *[static]*
- **`0x001A2F70`** - Overlay (in-game) UI sound listener (vtable `0x00469318`): kinds 1..6 map to events 11, 12, 10, 13, 9, 9. Created in `0x0022E968` on the overlay context (lodge, pause, results, pre-race, replay and map overlays). *[static]*

## `src/fe/feasyncfile.cpp`

Segment `0x001A36E8`-`0x001C58E8`.

- **`0x001A39F0`** - HUD update, called in the post-camera part of the game update. *[static]*
- **`0x001A7D40`** - cFEStateReadMessagePopup code; also handles online notification 0x109. *[static]*
- **`0x001A8770`** - Calls the online message pump `0x001A8B88`. *[static]*
  - `0x001A87B8`: Call site of the online message pump `0x001A8B88`. *[static]*
- **`0x001A8B88`** - Online message pump for the chat/lobby/online states: notification 0xEC plays UI sound ev 7, 0x109 plays ev 8. Called from `0x00194154` and `0x001A87B8`. *[static]*
  - `0x001A8D84`: Online notification 0xEC: UI sound ev 7 (snd 0x10). *[static]*
  - `0x001A8DB4`: Online notification 0x109 (probably message received): UI sound ev 8 (snd 0x11). *[unconfirmed]*
- **`0x001B3F78`** - Calls the FE music re-entry `0x0028FC58`. *[static]*
- **`0x001BCE38`** - Contains the cFEStateLobbyMenu selection of UIMenu button set 1 (right stick). *[static]*
  - `0x001BCE94`: cFEStateLobbyMenu selects UIMenu button set 1 (right stick). *[static]*
- **`0x001C2D18`** - cFEStateStats (online stats) state code. *[static]*
- **`0x001C2F00`** - Contains the cFEStateStats selection of UIMenu button set 1 (right stick). *[static]*
  - `0x001C31A8`: cFEStateStats selects UIMenu button set 1 (right stick). *[static]*
- **`0x001C4D28`** - Online stats next-tab (UIDown) handling of cFEStateStats `0x001C2D18`: plays UI sound kind 1 through the listener call at `0x001C4D2C`. *[static]*
  - `0x001C4D2C`: Listener call: online stats next tab (UIDown) plays kind 1. *[static]*
- **`0x001C4E40`** - Online stats previous-tab (UIUp) handling of cFEStateStats `0x001C2D18`: plays UI sound kind 1 through the listener call at `0x001C4E44`. *[static]*
  - `0x001C4E44`: Listener call: online stats previous tab (UIUp) plays kind 1. *[static]*

## `src/fe/fepopup.cpp`

Segment `0x001C58E8`-`0x001CE758`.

- **`0x001CA180`** - FE state with vtables `0x0046C890`/`0x0046CBD8` (input query not evaluated: jump tables). *[static]*
- **`0x001CAED8`** - BuyPopup input query: Cross plays sound 3 only. *[static]*
- **`0x001CB030`** - cKeyboardPopup code: the Fullkeyboard on-screen keyboard used by Player Name and Enter Cheat. Enter Cheat opens it empty with focus on 'q', with only Tab/Up/Down disabled. *[static]*
- **`0x001CDB98`** - cKeyboardPopup input: cursor/typing/shift play UI sound kind 1, Square help 5, Triangle close 6, Circle silent; the listener call is at `0x001CE254`. *[static]*
  - `0x001CE254`: Keyboard popup UI sound listener call (kinds 1 / 5 / 6). *[static]*
- **`0x001CE3C8`** - Disables a key of the keyboard popup; Player Name calls it ten times. *[static]*

## `src/fe/festaterewards.cpp`

Segment `0x001CF0B0`-`0x001D2678`.

- **`0x001CF0B0`** `cFEStateRewardGalleryBase_onCreateScreen` - Reward galleries update (Posters/Cards/Concept/Toys/Videos/CheatChars); Triangle goes back. *[static]*
  - `0x001CF28C`: Reward gallery Triangle = back: plays UI sound kind 3. *[static]*
  - Possible mismatch with the current name: The decomp name says onCreateScreen, but the records describe the reward galleries' update routine, including Triangle-back input handling.
- **`0x001D1AA0`** - cFEStatePreviewReward state code. *[static]*
- **`0x001D1FF0`** - Contains the cFEStatePreviewReward Triangle handling that closes the preview. *[static]*
  - `0x001D2028`: Preview reward Triangle closes the preview: plays UI sound kind 3. *[static]*
- **`0x001D23E0`** - MoviePlayer state ('MoviePlayer' object): plays an owned reward video full screen. *[static]*
- **`0x001D2518`** - MoviePlayer skip-button handling. *[static]*
- **`0x001D25E8`** - MoviePlayer: pauses the music for FMV playback. *[static]*
- **`0x001D2638`** - MoviePlayer movie end: resumes the music and returns to the rewards gallery. *[static]*

## `src/fe/ovstatelodge.cpp`

Segment `0x001D2678`-`0x001D4368`.

- **`0x001D2678`** `cFEStateMountainRoom_cFEStateMountainRoom` - cFEStateMountainRoom code. *[static]*
- **`0x001D2EA0`** - Contains the cFEStateMountainRoom Triangle handling that closes the help-text popup. *[static]*
  - `0x001D2EF0`: Mountain Room Triangle closes the help-text popup (`+0x48`, bit 6 = visible): plays UI sound kind 3. *[static]*
- **`0x001D3E08`** - PeakRoom input query: Cross plays sound 3 or the error sound; Triangle sound 3. *[static]*

## `src/fe/festatetrophyroom.cpp`

Segment `0x001D4368`-`0x001D66B0`.

- **`0x001D64C0`** - Calls the front-end audio init `0x00285FB0`. *[static]*

## `src/fe/fepopupmisc.cpp`

Segment `0x001DEB90`-`0x001E8FF0`.

- **`0x001DEC68`** - Contains the cFEPopupVideoCalibration (THX bars) confirm/close handling. *[static]*
  - `0x001DEDA8`: cFEPopupVideoCalibration (THX bars) confirmed/closed: plays UI sound kind 6. *[static]*
- **`0x001DEE10`** - cFEPopupScreenPos: Screen position popup (`24screen_position`) over Game Options. D-pad moves one step (Right/Up +1, Left/Down -1, clamped -20..20) on profile bytes `0x00535616` (x) / `0x00535615` (y); Cross keeps, Triangle restores. Applies the position live via vtable `+0x60` (`0x00393FB8`). *[PS2]*
- **`0x001DF050`** `cFEPopupScreenPos_onUpdate` - Contains the cFEPopupScreenPos (`24screen_position`) Cross confirm. *[static]*
  - `0x001DF074`: Screen position Cross confirms: plays UI sound kind 6. *[static]*
- **`0x001E1458`** - HUD update, called in the post-camera part of the game update. *[static]*
- **`0x001E1550`** - Rival reminders: posts the first unposted message of categories 1..3 (race) and 4..6 (jam) once. Needs the rival event open (`+0x278` bit 6+peak / 9+peak clear before this event) and no medal (`0x00145EF0`); text = first + r % 3, and the rival's own rider gets the second three. First of the career message functions (through `0x001E3100`) that draw from the visual RNG. *[static]*
- **`0x001E1C10`** - Rival taunt: posts a random item of category 28/29 + 2*peak that is not from the human and not already in the inbox (subject Foreshadow), while a standard event before the rival has no medal. *[static]*
- **`0x001E1DD0`** - Peak-challenge flags: silver or bronze in a peak event (modes 6..11) sets pending flag 40 + 4*peak + 2*jam (+1 for silver) unless already posted. *[static]*
- **`0x001E1EB8`** - Peak-challenge notices: pending flags 40..51 post 'your time has been beaten' (category 34 + jam + 2*peak); the first text after bronze, the second after silver, which also stops further ones. *[static]*
- **`0x001E2370`** - Stops rival taunts when the rival event opens: sets posted bits 28..33. *[static]*
- **`0x001E25D8`** - Backcountry result poster: on course 14 + peak dispatches to `0x001E2648` (rival race) or `0x001E2828` (rival jam); skipped when result bit 22+peak / 25+peak is set. Removes rival reminders (category 1+peak / 4+peak) and earlier results (`0x001E32C8`); a loss posts item 0x73 / 0x7F + 4*peak (+2 for the rival's own rider), a win sets the bit and posts the next item. Subject BCFinishWin/Loss. *[static]*
- **`0x001E2648`** - Backcountry rival race result message, dispatched from `0x001E25D8`. *[static]*
- **`0x001E2828`** - Backcountry rival jam result message, dispatched from `0x001E25D8`. *[static]*
- **`0x001E2A08`** - Relationship notice: posts a career message from a rival (args character, score) and signals the race HUD. Called by `0x00155BF0` (human's own record rises a level) and `0x00155E58` (every aged record). Gates: `0x005305F9` == 0, not the human's character, none of that character's messages posted (`0x001E3A30`), score > 15 + (r & 7). Category 12 + char (`0x001E2B38`) in `0x00441630`; item = first + r % count; both r are visual (presentation) RNG draws. *[static]*
- **`0x001E2B38`** - Maps a character to its relationship message category: returns 12 + character. *[static]*
- **`0x001E2EA0`** - Returns a message's From name: senders 0..9 are the riders, 10 kT_CMNGameTitle, 11 kT_CMNDJAtomica, 12 kT_FAQFolder. *[static]*
- **`0x001E2FE0`** - Adds a career message to the inbox (33 call sites in 12 functions); a full inbox first drops its oldest entry (`0x001E31B8`). The posters require Conquer the Mountain (`0x005305F9` == 0) and a tutorial counter outside 1..9. *[static]*
- **`0x001E3100`** - Picks the variant of a flag-1 message record: kinds 3/4 use r % 10, kind 5 r % 11, kind 8 r & 3 (end of the career message range from `0x001E1550` that draws from the visual RNG). *[static]*
- **`0x001E31B8`** - Drops the oldest inbox entry: shifts the entries and read bits up. Used by the inbox add `0x001E2FE0` when the inbox is full. *[static]*
- **`0x001E32C8`** - Removes rival reminder and earlier result messages from the inbox (can stop early); used by the backcountry result poster `0x001E25D8`. *[static]*
- **`0x001E3760`** - Earnings notice: posts item 247 (248) when earned + amount reaches the peak 1 (peak 2) earnings goal while peak 2 (peak 3) is locked. *[static]*
- **`0x001E38B8`** - Free-ride goal award notices: awards 11/12 post items 249/250, only while the next peak is still locked. *[static]*
- **`0x001E3A30`** - Tests whether a relationship message of a character is already posted. *[static]*
- **`0x001E3A78`** - Clears a character's relationship-message posted flag (when the score drops below 5). *[static]*
- **`0x001E3C00`** - Opens the Progression/Rewards FAQ folder while the Message Center is shown, when entered with `0x004A20CC` (gp-0x1024) != -1. Which path sets that global is unknown; the observed MCOMM path leaves all folders closed. *[static]*
- **`0x001E4200`** - Contains the FAQ folder open/close toggle (inbox posted bits 7..11). *[static]*
  - `0x001E4338`: FAQ folder toggle block: opens/closes a folder through inbox posted bits 7..11. *[static]*
- **`0x001E4578`** - Message centre state code (input query not evaluated: jump tables). *[static]*
- **`0x001E4F70`** - Formats a career message subject by record kind: kind 3 kT_MSGSubjectBCFinishWin/Loss<v> (Win for the odd items from 0x74, jump table `0x0046E1E0`), 4 Foreshadow<v>, 5 Aggression<v>, 8 BeatThePeak<v>; other kinds use the record's own subject. *[static]*
- **`0x001E5AA0`** - Rewrites results item 0 to 'To semi final round' / 'To Final Round' when advancing, else Transport. *[PS2]*
- **`0x001E5B80`** - `42freestyle_standings` screen code; the results rows read the give-up flag `0x005366D0`. *[static]*
  - `0x001E5F6C`: Results rows read the give-up flag `0x005366D0`. *[static]*
  - `0x001E6594`: Freestyle standings rows filled and panel shown: UI ev 14. *[static]*
- **`0x001E6630`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001E6668`** - `43final_standings` screen code. *[static]*
  - `0x001E78F4`: Final standings panel shown: UI ev 14. *[static]*
- **`0x001E7B78`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001E7BB0`** - finishov screen routine (screendata/3D Ov groups). *[static]*
  - `0x001E805C`: finishov results group shown: UI ev 14. *[static]*
- **`0x001E81B0`** - finishov input query: Cross plays sound 3 or 0, others 0 (paired with `0x001E88D0`). *[static]*
- **`0x001E8200`** - finishov screen routine (screendata/3D Ov groups). *[static]*
  - `0x001E8780`: finishov results group shown: UI ev 14. *[static]*
- **`0x001E88D0`** - finishov input query: Cross plays sound 3 or 0, others 0 (paired with `0x001E81B0`). *[static]*
- **`0x001E8920`** - `70peakchal_results` screen code (peak-challenge results); the finish panel setup reads the give-up flag `0x005366D0`. *[static]*
  - `0x001E8D38`: Finish panel setup reads the give-up flag `0x005366D0`. *[static]*
  - `0x001E8EEC`: Peak-challenge results panel shown: UI ev 14. *[static]*
  - `0x001E8FA4`: Peak-challenge OV_darkblue page shown: UI ev 14. *[static]*
- **`0x001E8E98`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001E8FC0`** - Peak-challenge help page code. *[static]*

## `src/fe/ovstatehud.cpp`

Segment `0x001E8FF0`-`0x001F3790`.

- **`0x001E8FF0`** `cOVStateHiScoreList_onCreateScreen` - Contains the help page switch (helptxt01/02) that plays UI ev 14. *[static]*
  - `0x001E9114`: Help page helptxt01/02 switched: UI ev 14. *[static]*
  - Possible mismatch with the current name: The decomp name says cOVStateHiScoreList onCreateScreen, but the only fact recorded inside is a help-page (helptxt01/02) switch with a UI sound, as in the adjacent peak-challenge help page code.
- **`0x001E91A8`** - HUD placement helper, executed on the active-letter path of the HUD letter draw. *[static]*
- **`0x001E91F8`** - HUD placement helper used by the letter draw. *[static]*
- **`0x001E9220`** - HUD placement helper used by the letter draw. *[static]*
- **`0x001E92A8`** - Uber hint layout: FEFONT at 0.7, text runs split at '@', icons from `0x004C8980`. Runs are measured by `0x003921F0`; height = max(29 x 0.7, tallest icon); icons are not scaled. *[PS2]*
- **`0x001E94E0`** - Toggles additional HUD text when the flash widget fraction is exactly 1. *[static]*
- **`0x001E95A0`** - Uber hint draw at descriptor 73 (320,460): centered, bottom-aligned, white, (2,2) shadow. Needs per-player flag bits 21 and 24 plus pre-pass bit 25. *[PS2]*
- **`0x001E9A30`** - Single-player HUD slot draw: switches on the slot type through jump table `0x0046EC70`. Also draws the blinking 'Press X to skip' prompt ('%s @skip %s', kT_OVRCMNPress + kT_OVRCMNToSkip) while a step is skippable. One of the candidate sites (`0x001E9A30`/`0x001EABB0`/`0x001EC2E0`/`0x002204A0`) for the Now Playing (EA RADIO BIG) popup: unlocalized header in HUDFONT x0.8, title wrapped at 300 px in FEFONT x0.6, three-slice OV_1-4 box at (20, 460-H); slide in 0-0.4 s, text fade in 0.4-0.8, hold to 7.2, fade out to 7.6, slide out to 8.0; the same title is ignored while showing. *[PS2]*
- **`0x001E9AD0`** `cOVStateHUD1P_onCreateScreen` - HUD init: seeds the Uber hint variant from the visual RNG, and draws from the visual RNG during load-time audio/HUD set-up (`0x001EA800`). *[PS2]*
  - `0x001EA1CC`: Copies the renderer `+0xF50` texture handle into HUD owner `+0x474` (through `0x001EA1E0`). *[static]*
  - `0x001EA800`: Visual (presentation) RNG draw during load-time audio/HUD set-up. *[PS2]*
- **`0x001EA930`** - HUD update (vtable entry `0x004741C4`): sets the HUD flags (owner `+0x3CC` from table `0x00478078` by mode byte `0x00535C12`), runs the pre-pass (at `0x001EBCA4`) and the place-change animation (1st place scales 1+sin(4*pi*t)*0.1996*(1-t^2), others alpha 0.5t+0.5). Per-tick order: draw `0x001EC3F8` -> this update -> provider `0x00127998` -> rider post `0x00121750` -> `0x00117C28`. Adds the OPPONENT HUD line (0x08000000) for event kind 6. *[PS2]*
  - `0x001EABB0`: Block listed as the Now Playing (EA RADIO BIG) HUD popup (one of several candidate sites; see `0x001E9A30`). *[static]*
  - `0x001EB160`: Freestyle standings row builder block. *[static]*
  - `0x001EB350`: Big Challenge HUD block: badge with challenge number, clock HH:MM:SS.hh (red at 0), COUNT n / N, GOAL n, HEIGHT n.nnm; collectible counter hidden. *[PS2]*
  - `0x001EB6E4`: Mail icon update block: advances a 1 s blink phase and a 5 s timer. *[PS2]*
  - `0x001EB9E8`: Finish block: sets HUD state `+0x88` = rider `+0x480` ? 2 : 1. *[PS2]*
  - `0x001EB9FC`: Finish check: after the finish the Uber hint is not drawn. *[static]*
  - `0x001EBC10`: 1st-place glow timer: place object `+0x4C` += 0.026782159 per tick, wraps 0..2, -1 when not leading. *[static]*
  - `0x001EBC94`: Pre-pass code writing the HUD state phases `+0x64` / `+0x68` (through `0x001EBF2C`). *[static]*
  - `0x001EBCA4`: Uber hint / gauge flash pre-pass, probably a point inside the HUD update, not a function entry: flips owner `+0x55C` when Tricky slot 9 value/max == 1; grants bit 25 when slot 9 is live, ratio != 1, and no live slot of type 0, 0x21 or 0xB. *[PS2]*
  - `0x001EBDF4`: Flash phase clock (through `0x001EBE60`): slot 9 absent or fraction 1 -> -1; negative -> 1; else += (1/30)/((1-f)*0.9104143977165222 + 0.029972560703754425), wrapping while > 2. *[static]*
  - `0x001EBED4`: Pending-letter phase clock (through `0x001EBF2C`): slot 10 absent -> -1; negative -> 0.5; else += 0.08791634440422058, wrapping while > 1. *[static]*
- **`0x001EC1F0`** - Contains a block listed as the Now Playing (EA RADIO BIG) popup and the HUD event handling in which event 8 (new message) starts the mail icon. *[PS2]*
  - `0x001EC2E0`: Block listed as the Now Playing (EA RADIO BIG) HUD popup (one of several candidate sites; see `0x001E9A30`). *[static]*
  - `0x001EC3C4`: HUD event handling block: event 8 (new message) sets hud `+0x160`, starting the mail icon. The notice reaches the hud object (hash of 'hud' under G+0x48) through its virtual `+0xC4` with 8. *[PS2]*
- **`0x001EC3F8`** `cOVStateHUD1P_onRender2D` - HUD draw (vtable entry `0x004741DC`): draws the HUD bank as of the previous tick. The clock element (bit 0x4, descriptor 0x1A) counts down int(limit/60)*60 - race ticks. *[PS2]*
  - `0x001EC9F0`: Selects the single-player HUD state at owner `+0x48` (through `0x001EC9F8`). *[static]*
  - `0x001ECC74`: HUD renderer reads the slot `+0xC` count (also at `0x001ECC84`). *[static]*
  - `0x001ECD60`: Ordinary boost gauge colour ramp block (palette `0x004C84C8` / `0x004C84E8` / `0x004C8508`). *[static]*
  - `0x001ECFFC`: Freestyle standings draw (type-7 case): three rows at descriptor 0x17 (20,20) from the `0x001EB160` rows, best first; the player row (score `+0x198` plus heat-2 carry) goes where it is at least the posted score. *[PS2]*
  - `0x001ED5C8`: OPPONENT line block (type-7 case, to `0x001ED78C`): label (`0x0046EB60`) at (20,65), value at (20,78), scale 0.7; N = opp `+0x198` - player `+0x198`, '+%d' if N >= 0; colours `0x004C88C8` N>0, `0x004C88A8` -5000..0, `0x004C8888` below. *[PS2]*
  - `0x001ED790`: Slot type 8 (earned SUPER UBER letters) draw block: loop to `0x001ED8F4` calls `0x0021ED48` in index order; boundaries advance by 1/9 of the smoothed fraction; scale-pop coefficient 1.80013132 (`0x0049DA38`, gp-0x56B8). *[static]*
  - `0x001EF6AC`: Pending-Uber-letter preview draw (to `0x001EF7A0`), driven by slot 10 and HUD state `+0x68`: mode 1 letters after the active prefix, x scale (phase-0.5)*2. Not a removal transition. *[static]*
- **`0x001EF7BC`** - Contains HUD gauge drawing: the orb animation and glow, flash background substitution, coil/stem glow submissions, the inactive letter loop, the Uber hint draw after the slot loop, and the mail icon draw. *[PS2]*
  - `0x001EFC58`: Orb animation (to `0x001EFD38`), active when HUD state `+0x64` >= 0: active orb uses state colour `+0x54`, width x phase for phase < 1, else 2-phase; inactive orb uses the descriptor colour. *[static]*
  - `0x001EFC9C`: Loads the orb sprite owner `+0x538` with descriptor 3 (through `0x001EFDB0`). *[static]*
  - `0x001EFDB4`: Orb glow: expands the glow rectangle and calls `0x0021E7E0` while phase >= 0. *[static]*
  - `0x001EFE94`: Flash background substitution (to `0x001F0040`): during an active flash gray coil group 0 is palette-tinted and widget 5 swaps gray stem group 1 for white stem group 3 (tinted); fills stay white. *[static]*
  - `0x001F0108`: End of the coil/stem glow submissions (orb, three coil sections, stem). *[static]*
  - `0x001F0110`: Inactive letter loop (to `0x001F01D0`): from the stack `+0x33C` index through 8, changing font shadow offsets. *[static]*
  - `0x001F0228`: Uber hint draw after the HUD slot loop. *[PS2]*
  - `0x001F0F3C`: Mail icon draw block: OV.LUI mail_icon at (15,384) of 640x480, white (`0x004C8788`) while the phase <= 0.5, else orange (`0x004C87A8`). *[PS2]*
- **`0x001F10F8`** - HUD placement helper used by the letter draw. *[static]*
- **`0x001F1190`** - HUD sprite submission. *[static]*
- **`0x001F14B0`** - Scatters lost-point digits for HUD types 0x25/0x27/0x28. *[static]*
- **`0x001F1B30`** - HUD text draw helper. *[static]*
- **`0x001F1E28`** - HUD lerped text draw helper. *[static]*
- **`0x001F2AA0`** - HUD wrapped text draw helper (used for trick names). *[static]*
- **`0x001F30D8`** - Draws the yellow 'Loading...' caption with the turning snowflake while world-state bit 2 is set. *[PS2]*
- **`0x001F3188`** - HUD update, called in the post-camera part of the game update. *[static]*
- **`0x001F3700`** - cFEStateLodge code (overlay context; uses the overlay UI events 9..13). *[static]*

## `src/fe/festatelodge.cpp`

Segment `0x001F3790`-`0x001F4830`.

- **`0x001F3CC8`** - Lodge input query: Cross plays sound 3 only. *[static]*
- **`0x001F3FF8`** - cFEStateLodgeRiderDetail code (overlay context). *[static]*
- **`0x001F4050`** `cFEStateLodgeRiderDetail_onCreateScreen` - Sets up the Lodge Rider Details screen (`155rider_details_conquer`): Rewards, Trophies, Cheat Characters, Ubertrick Setup, Career Highlights, Player Name, Rider Profile, with the same states and help texts as `154rider_details`. *[static]*
- **`0x001F4728`** - cFEStateBuyAttrib code (buy attribute points). *[static]*

## `src/fe/festatebuyattrib.cpp`

Segment `0x001F4830`-`0x001F7198`.

- **`0x001F4A90`** - Contains the cFEStateBuyAttrib Cross purchase check. *[static]*
  - `0x001F4B40`: BuyAttrib Cross with too little cash: UI sound kind 4, else opens the 'UITRICKBUY' popup. *[static]*
- **`0x001F4C30`** - Contains the cFEStateBuyAttrib Left/Right handling (take back or add an attribute point). *[static]*
  - `0x001F4D0C`: BuyAttrib Left with nothing pending to take back: kind 4 (error). *[static]*
  - `0x001F4E18`: BuyAttrib Left refund / Right add succeeded: kind 1. *[static]*
  - `0x001F4E4C`: BuyAttrib Right at max level 11, over cap or not enough cash: kind 4 (error). *[static]*
- **`0x001F54B0`** - cFEStateCareerStats code. *[static]*
- **`0x001F56C8`** `cFEStateCareerStats_onInputBegin` - Contains the career stats Up/Down list scrolling. *[static]*
  - `0x001F59EC`: Career stats Up/Down scrolls the list: kind 2, or kind 4 at the top/bottom. *[static]*
- **`0x001F5A38`** - Career Highlights page switch; hides the other pages' groups. *[static]*
- **`0x001F5DA0`** `cFEStateCareerStats_setupHighlightsList` - Front-end monster trick unlocks and Career Highlights row fill. Position p (order `0x00441B40`) is unlocked when p % 3 < medal[p/3] (profile byte `+0xBB8`+s). Row r: hl<r> = '%s%d' of `0x00441BA0`[stat]; checkmark/checkbox by tier < medal; hlsec<r> = '%s Monster Trick'; the trick or kT_FEUnlockMonsterTrick; scroll arrows. *[PS2]*

## `src/fe/ovstateenterlodge.cpp`

Segment `0x001F7198`-`0x001F8168`.

- **`0x001F7590`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001F77F0`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001F7958`** - `61toptimes` screen code. *[static]*
  - `0x001F7E30`: Top-times panel filled: UI ev 14. *[static]*
- **`0x001F80C8`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*

## `src/fe/ovtemplatepausemenu.cpp`

Segment `0x001F8168`-`0x001F9188`.

- **`0x001F8168`** `cOVTemplate_PauseMenu_onCreateScreen` - Pause page `31paus_freeride` routine; calls `0x00289B70` but plays no UI sound itself. *[static]*
- **`0x001F8908`** - Pause family input query: Cross returns 0 (the state plays the sound itself at `0x001F8998`), Triangle 0x101 (ev 9, sound 3). *[static]*
- **`0x001F8948`** `cOVTemplate_PauseMenu_onWidgetEvent` - Pause menu item event handler (notify 5 = Cross, notify 6 = Triangle). *[static]*
  - `0x001F8998`: Pause Cross on an enabled item (state `+0xD8`[id] != 0): kind 6, then trans_out and the action; a greyed item plays kind 4. *[static]*
  - `0x001F8B3C`: Creates the in-game audio options state (`0x00195FF0`) with flag 0. *[static]*
  - `0x001F8BFC`: Pause Triangle (notify 6): pops the page and calls resume `0x00289BB8`; the engine plays ev 9 (sound 3). *[static]*
- **`0x001F8DF8`** - In-game Options screen (`37beoptions`): HUD, Camera 1/2, Music/MC, SFX, Character speech, DJ Speech, Arcade SFX, Save game. *[static]*

## `src/fe/ovstatepause.cpp`

Segment `0x001F9188`-`0x00200218`.

- **`0x001FAA78`** - In-game options input query (A8: Cross 0x100; B0: L/R 0x101, Triangle 0x100); Cross/Triangle play sound 3. *[static]*
- **`0x001FB588`** - Round card / pre-event (career objectives) screen enter: plays UI sound 0xE and requests PA_Sponsor_Intro (`0x002A31C0`) for qualifiers. *[PS2]*
- **`0x001FB6B8`** - `40race_pre` screen code (pre-event info panel). *[static]*
  - `0x001FBB90`: Race pre-event panel appears: UI ev 14, then DJ/PA `0x002A31C0`. *[static]*
- **`0x001FBD20`** - `41freestyle_pre` screen code (pre-event info panel). *[static]*
  - `0x001FC844`: Freestyle pre-event panel appears: UI ev 14, then `0x002A31C0`. *[static]*
- **`0x001FC878`** - `50multifs_pre` screen code (multiplayer freestyle pre-event info panel). *[static]*
  - `0x001FD104`: Multiplayer freestyle pre-event panel appears: UI ev 14, then `0x002A31C0`. *[static]*
- **`0x001FD190`** - Builds the `68rival_pre` objectives card for peak runs (Rival Challenge / route / pass / Time to beat). Rival name from `0x00145750` for the current course's peak; All Peak uses the Peak 1 route string; mode 8 never offers a pass. *[static]*
- **`0x001FD268`** - `68rival_pre` screen code. *[static]*
  - `0x001FD304`: Rival panel appears: UI ev 14. *[static]*
- **`0x001FDB78`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
- **`0x001FF748`** - `62reward_list` state code (input query not evaluated: jump tables). *[static]*

## `src/fe/uitemplatemap.cpp`

Segment `0x00200700`-`0x002086A8`.

- **`0x00200AC0`** - Contains a call to the Map/Transport open `0x0028F5B8` (Map overlay). *[static]*
  - `0x00200ADC`: Call to the Map/Transport open `0x0028F5B8` (Map overlay). *[static]*
- **`0x002018A8`** - EventSelect logic item events (forwarded from cFEStateEventSelect `0x00186610`): Cross select plays kind 6 and a locked item kind 4; Square on the peak goals list plays kind 6; Triangle plays nothing. Listener call at `0x002018C8`. Also restores free ride from the map: event type 4, game mode 12, free-ride handler (same course -> world state 15). *[PS2]*
  - `0x002018C8`: EventSelect UI sound listener call. *[static]*
  - `0x0020193C`: EventSelect Cross (ev 5) branch start. *[static]*
  - `0x002019A4`: EventSelect select event/peak/goal: accept sound (kind 6). *[static]*
  - `0x00201BD8`: EventSelect select: accept sound (kind 6). *[static]*
  - `0x00201D34`: EventSelect select: accept sound (kind 6). *[static]*
  - `0x00201D68`: EventSelect locked item: error sound (kind 4). *[static]*
  - `0x00201DD8`: EventSelect select: accept sound (kind 6). *[static]*
  - `0x00201EA4`: EventSelect select: accept sound (kind 6). *[static]*
  - `0x002020C8`: EventSelect select: accept sound (kind 6). *[static]*
  - `0x002021C0`: EventSelect locked item: error sound (kind 4). *[static]*
  - `0x002022BC`: EventSelect Square branch start (peak goals list). *[static]*
  - `0x00202380`: EventSelect Square peak goals list: accept sound (kind 6). *[static]*
  - `0x002023AC`: EventSelect Square peak goals list: accept sound (kind 6). *[static]*
- **`0x00202738`** - Returns whether the event-select logic owns input (state `+0x48`); used by the EventSelect input query `0x00186950`. *[static]*

## `src/fe/ovstatemap.cpp`

Segment `0x002086A8`-`0x0020A778`.

- **`0x002087F0`** `cOVState_MAP_onGainTransition` - Contains the map session list labelling (top/bottom of run). *[static]*
  - `0x00208840`: Session list labelling block: first item kT_CMNTopOfRun, last kT_CMNBottomOfRun unless there are only two. *[static]*

## `src/fe/ovtemplatedialog.cpp`

Segment `0x0020A778`-`0x0020DE30`.

- **`0x0020CCF8`** - Contains the results 'Transport' selection, which switches to world state 14 (arg 2) via `0x00236250`. *[PS2]*
  - `0x0020CF80`: Results 'Transport' selection -> world state 14 arg 2 (`0x00236250`). *[PS2]*
- **`0x0020D1D8`** - Pause menu handler family code (the family includes the Give Up case at `0x0020DA58`). *[static]*
- **`0x0020D308`** - Pre-race/results-type panel input query: Cross plays sound 3, others 0. Same behaviour: `0x001FDB78`, `0x001F80C8`, `0x001F77F0`, `0x001F7590`, `0x001E8E98`, `0x001E7B78`, `0x001E6630`, `0x002453E0`, `0x00246268`. *[static]*
- **`0x0020D568`** - Yes/no dialog input query: Cross/Triangle play sound 3. *[static]*
- **`0x0020D590`** `cOVTemplate_Dialog_onWidgetEvent` - Dialog widget events for the pause confirmations, including the Restart confirm path and the Give Up case. *[PS2]*
  - `0x0020D7DC`: Restart confirm path -> `0x002302A8` -> world state 1 arg 2 (gondola ride-up, then the card). *[PS2]*
  - `0x0020DA58`: Pause menu Give Up case: closes the menu, calls `0x001253D0(human)`, sets `0x004A26FC` (gp-0x9F4) = 3 and `0x004A2A50` (gp-0x6A0) from table `0x004428F0`. The Single Event pause menu has no Give Up. *[PS2]*

## `src/fe/ovstatereplay.cpp`

Segment `0x0020DE30`-`0x0020E938`.

- **`0x0020DF10`** - Replay state input query: returns 0 for every button (silent). *[static]*
- **`0x0020DF38`** - `64replay` menu input: ReplayMenuUp/Down slide the panel (UI sound kind 2); Start opens 'ReplayMenu' (kind 6); Cross continue/exit (kind 6). Listener call at `0x0020DF58`. *[static]*
  - `0x0020DF58`: Replay menu UI sound listener call (kinds 2 / 6). *[static]*

## `src/fe/ovstatetrophy.cpp`

Segment `0x0020E938`-`0x002111A0`.

- **`0x0020EDA0`** - Race progress meter HUD. *[static]*
- **`0x002105B0`** - Called with rider `+0x86C` in the tail of `0x0011D660`. *[static]*

## `src/fe/festateloadscreen.cpp`

Segment `0x00233438`-`0x00234AD0`.

- **`0x00233640`** - Loading screen routine that stops the loading loop via `0x0028FA98(1.0)`; probably the stop counterpart of `0x00233048` (pairing inferred from listing order). *[unconfirmed]*
- **`0x00233AA0`** - Rolling start: the race clock goes PreRace -> Race without a countdown. The ready state already holds both riders in control 0 / motion 0 with a start velocity, and on game tick 0 both leave the ground. *[PS2]*
- **`0x00233C10`** - Uses the game update copy `0x00244880`. *[static]*
- **`0x00233C50`** - World state 5 (finish) function: finish camera. *[static]*
- **`0x00233CD8`** - World state 5 (post-finish) update: waits until every human is below 277.78 cm/s (`0x0049DF7C`, gp-0x5174); results/replay start 408 ticks after a FINISH and 288 after TIME'S UP. For a CTM final with one human in 1st-3rd it queues the podium via `0x0027AC60`, then goes to world state 12. *[PS2]*
  - `0x00233F20`: Event setup block: calls the relationship ageing `0x00155E58`. *[static]*
- **`0x00234008`** - Race results overlay; calls the camera restore `0x00162290`. *[static]*
- **`0x002341D0`** - World state 1 enter: queues the event-intro NIS list (CTM: `0x0027AAF8` with table `0x00481E48`). *[PS2]*
  - `0x002342B8`: Block writing the race copy of the participants at `0x00535B20`. *[static]*
- **`0x002343B0`** - World state 1 update: the intro plays, CPU riders load, and grid placement happens when the NIS list reaches the idle. *[static]*
- **`0x00234750`** - World state 1 exit. *[static]*
  - `0x002348AC`: Event setup block: calls the relationship ageing `0x00155E58`. *[static]*
- **`0x00234A30`** - Countdown routine that calls the countdown beep `0x0029C420`. *[static]*

## `src/fe/festateloadhint.cpp`

Segment `0x00245950`-`0x00247E60`.

- **`0x00245950`** `cFELoadHintState_onCreateScreen` - `101QPMPHints` enter: shows one rotating load-screen hint (kT_FEHINTTitle%d / kT_FEHINTDES%d) and advances the hint counter. Uses n = counter + 1 over the 15 hints from CMNAMER, skipping hint 12 (Bragging Rights); then counter = (counter + 1) % 15. The counter is byte `0x004A2C38` (gp-0x4B8), initially 0. *[static]*
- **`0x00246268`** - Pre-race/results/toptimes/bc_fail/progressive panel input query: Cross plays sound 3, others 0. *[static]*
