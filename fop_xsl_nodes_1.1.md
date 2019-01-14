#fo nodes
##fo:root
```
(layout-master-set,declarations?,bookmark-tree?,(page-sequence|page-sequence-wrapper)+)
```

#fo attributes
##Common Accessibility Properties
- source-document: <uri-specification> [<uri-specification>]* | none | inherit
- role: <string> | <uri-specification> | none | inherit

##Common Absolute Position Properties
- absolute-position: auto | absolute | fixed | inherit
- top,bottom,left,right: <length> | <percentage> | auto | inherit

##Common Aural Properties
- azimuth: <angle> | [[ left-side | far-left | left | center-left | center | center-right | right | far-right | right-side ] || behind ] | leftwards | rightwards | inheri
- cue-after,cue-before: <uri-specification> | none | inherit
- elevation: <angle> | below | level | above | higher | lower | inherit
- pause-after,pause-before: <time> | <percentage> | inherit
- pitch: <frequency> | x-low | low | medium | high | x-high | inherit
- pitch-range:	<number> | inherit
- play-during: <uri-specification> mix? repeat? | auto | none | inherit
- richness: <number> | inherit
- speak: 	normal | none | spell-out | inherit
- speak-header: once | always | inherit
- speak-numeral: digits | continuous | inherit
- speak-punctuation: 	code | none | inherit
- speech-rate: <number> | x-slow | slow | medium | fast | x-fast | faster | slower | inherit
- stress: <number> | inherit
- voice-family:	[[<specific-voice> | <generic-voice> ],]* [<specific-voice> | <generic-voice> ] | inherit
- volume:	<number> | <percentage> | silent | x-soft | soft | medium | loud | x-loud | inherit

## Common Border, Padding, and Background Properties
- background-attachment:	scroll | fixed | inherit
- background-color:	<color> | transparent | inherit
- background-image:	<uri-specification> | none | inherit
- background-repeat:	repeat | repeat-x | repeat-y | no-repeat | inherit
- background-position-horizontal:	<percentage> | <length> | left | center | right | inherit
- background-position-vertical:	<percentage> | <length> | top | center | bottom | inherit
- border-[before|after|start|end|top|bottom|left|right]-color: <color> | transparent | inherit
- border-[before|after|start|end]-style: <border-style> | inherit  (none | hidden | dotted | dashed | solid | double | groove | ridge | inset | outset)
- border-[before|after|start|end]-width: <border-width> (thin | medium | thick) | <length-conditional> | inherit
- padding-[before|after|start|end|top|bottom|left|right]: <padding-width> | <length-conditional> | inherit

## Common Font Properties
- font-family: 	[[ <family-name> | <generic-family> ],]* [<family-name> | <generic-family>] | inherit
- font-selection-strategy:	auto | character-by-character | inherit
- font-size: <absolute-size> | <relative-size> | <length> | <percentage> | inherit  [ xx-small | x-small | small | medium | large | x-large | xx-large ] [ larger | smaller ]
- font-stretch: normal | wider | narrower | ultra-condensed | extra-condensed | condensed | semi-condensed | semi-expanded | expanded | extra-expanded | ultra-expanded | inherit  [ultra-condensed | extra-condensed | condensed | semi-condensed | normal | semi-expanded | expanded | extra-expanded| ultra-expanded]
- font-size-adjust: 	<number> | none | inherit
- font-style: normal | italic | oblique | backslant | inherit
- font-variant: normal | small-caps | inherit
- font-weight: 	normal | bold | bolder | lighter | 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900 | inherit

##Common Hyphenation Properties
- country: none | <country> | inherit
- language: none | <language> | inherit
- script: none | auto | <script> | inherit
- hyphenate: 	false | true | inherit
- hyphenation-character:	<character> | inherit
- hyphenation-push-character-count:	<number> | inherit
- hyphenation-remain-character-count: <number> | inherit

##Common Margin Properties-Block
- margin-top|bottom|right|lef:	<margin-width> | inherit
- space-before|after|end|start:  <space> | inherit (	space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0)
- start|end-indent: <length> | <percentage> | inherit
- top|bottom|right|left: 
- relative-position: static | relative | inherit

##Area Alignment Properties
alphabetic | ideographic | hanging | mathematical | central | middle | text-before|after-edge | before|after-edge
- alignment-adjust|alignment-baseline: auto | baseline | before-edge | text-before-edge | middle | central | after-edge | text-after-edge | ideographic | alphabetic | hanging | mathematical | <percentage> | <length> | inherit
- baseline-shift:	baseline | sub | super | <percentage> | <length> | inherit
- display-align: auto | before | center | after | inherit
- dominant-baseline:	auto | use-script | no-change | reset-size | ideographic | alphabetic | hanging | mathematical | central | middle | text-after-edge | text-before-edge | inherit
- relative-align:	before | baseline | inherit

##Area Dimension Properties
- allowed-height|width-scale: [ any | <percentage> ]* | inherit
- block-progression-dimension:	auto | <length> | <percentage> | <length-range> | inherit
- content-height|width: 	auto | scale-to-fit | scale-down-to-fit | scale-up-to-fit | <length> | <percentage> | inherit
- height|width:	<length> | <percentage> | auto | inherit
- inline-progression-dimension:	auto | <length> | <percentage> | <length-range> | inherit
- max-height|width:	<length> | <percentage> | none | inherit
- min-height|width:	<length> | <percentage> | inherit
- scaling: uniform | non-uniform | inherit
- scaling-method: auto | integer-pixels | resample-any-method | inherit

##Block and Line-related Properties
- hyphenation-keep: auto | column | page | inherit
- last-line-end-indent:  <length> | <percentage> | inherit
- line-height: normal | <length> | <number> | <percentage> | <space> | inherit
- line-height-shift-adjustment: consider-shifts | disregard-shifts | inherit
- line-stacking-strategy: line-height | font-height | max-height | inherit
- linefeed-treatment: ignore | preserve | treat-as-space | treat-as-zero-width-space | inherit
- white-space-treatment:	ignore | preserve | ignore-if-before-linefeed | ignore-if-after-linefeed | ignore-if-surrounding-linefeed | inherit
- text-align:	start | center | end | justify | inside | outside | left | right | <string> | inherit
- text-align-last:	relative | start | center | end | justify | inside | outside | left | right | inherit
- text-indent: <length> | <percentage> | inherit
- white-space-collapse:	false | true | inherit
- wrap-option: no-wrap | wrap | inherit

##Character Properties
- character: <character>
- letter-spacing: normal | <length> | <space> | inherit
- suppress-at-line-break: auto | suppress | retain | inherit
- text-decoration:	none | [ [ underline | no-underline] || [ overline | no-overline ] || [ line-through | no-line-through ] || [ blink | no-blink ] ] | inherit
- text-shadow:	none | [<color> || <length> <length> <length>? ,]* [<color> || <length> <length> <length>?] | inherit
- text-transform:	capitalize | uppercase | lowercase | none | inherit
- treat-as-word-space:	auto | true | false | inherit
- word-spacing: 	normal | <length> | <space> | inherit

##Color-related Properties
- color: 	<color> | inherit
- color-profile-name: <name> | inherit
- rendering-intent:	auto | perceptual | relative-colorimetric | saturation | absolute-colorimetric | inherit

##Float-related Properties
- clear:	start | end | left | right | inside | outside | both | none | inherit
- float:	before | start | end | left | right | inside | outside | none | inherit
- intrusion-displace:	auto | none | line | indent | block | inherit

##Keeps and Breaks Properties
- break-after|before:	auto | column | page | even-page | odd-page | inherit
- keep-together:	<keep> | inherit (.within-line=auto, .within-column=auto, .within-page=auto)
- keep-with-next|previous: <keep> | inherit
- orphans: <integer> | inherit
- widows: <integer> | inherit

##Layout-related Properties
- clip: <shape> | auto | inherit
- overflow: visible | hidden | scroll | error-if-overflow | repeat | auto | inherit
- reference-orientation: 0 | 90 | 180 | 270 | -90 | -180 | -270 | inherit
- span:	none | all | inherit

##Leader and Rule Properties
- leader-alignment: none | reference-area | page | inherit
- leader-pattern:	space | rule | dots | use-content | inherit
- leader-pattern-width:	use-font-metrics | <length> | <percentage> | inherit
- leader-length:	<length-range> | <percentage> | inherit
- rule-style: none | dotted | dashed | solid | double | groove | ridge | inherit
- rule-thickness: <length>

##Properties for Dynamic Effects Formatting Objects
- active-state: link | visited | active | hover | focus
- auto-restore:	true | false
- case-name: <name>
- case-title: <string>
- destination-placement-offset: <length>
- external-destination: empty string | <uri-specification>
- indicate-destination: true | false
- internal-destination:	empty string | <idref>
- show-destination: replace | new
- starting-state:	show | hide
- switch-to: 	xsl-preceding | xsl-following | xsl-any | <name>[ <name>]*
- target-presentation-context: use-target-processing-context | <uri-specification>
- target-processing-context:	document-root | <uri-specification>
- target-stylesheet: use-normal-stylesheet | <uri-specification>

##Properties for Indexing
- index-class: <string>
- index-key:	<string>
- page-number-treatment: link | no-link
- merge-ranges-across-index-key-references:	merge | leave-separate
- merge-sequential-page-numbers: merge | leave-separate
- merge-pages-across-index-key-references: merge | leave-separate
- ref-index-key:<string>

7.25 Marker Properties
- marker-class-name:	<name>
- retrieve-boundary-within-table: table | table-fragment | page
- retrieve-class-name:	<name>
- retrieve-position:	first-starting-within-page | first-including-carryover | last-starting-within-page | last-ending-within-page
- retrieve-boundary: page | page-sequence | document
- retrieve-position-within-table:	first-starting | first-including-carryover | last-starting | last-ending

##Properties for Number to String Conversion
- format: <string>
- grouping-separator: <character>
- grouping-size: <number>
- letter-value: auto | alphabetic | traditional

##Pagination and Layout Properties
- blank-or-not-blank:	blank | not-blank | any | inherit
- column-count: <number> | inherit
- column-gap: <length> | <percentage> | inherit
- extent: <length> | <percentage> | inherit
- flow-name: <name>
- force-page-count: auto | even | odd | end-on-even | end-on-odd | no-force | inherit
- initial-page-number: auto | auto-odd | auto-even | <number> | inherit
- master-name: <name>
- master-reference:	<name>
- maximum-repeats: <number> | no-limit | inherit
- media-usage:	auto | paginate | bounded-in-one-dimension | unbounded
- odd-or-even:	odd | even | any | inherit
- page-height: auto | indefinite | <length> | inherit
- page-position:only | first | last | rest | any | inherit
- page-width: auto | indefinite | <length> | inherit
- precedence:	true | false | inherit
- region-name:	xsl-region-body | xsl-region-start | xsl-region-end | xsl-region-before | xsl-region-after | <name>
- flow-map-name: <name>
- flow-map-reference:	<name>
- flow-name-reference: <name>
- region-name-reference:	<name>

7.28 Table Properties
- border-after-precedence: force | <integer> | inherit
- border-before-precedence:	force | <integer> | inherit
- border-collapse:	collapse | collapse-with-precedence | separate | inherit
- border-end-precedence:	force | <integer> | inherit
- border-separation:	<length-bp-ip-direction> | inherit
- border-start-precedence: 	force | <integer> | inherit
- caption-side:	before | after | start | end | top | bottom | left | right | inherit
- column-number: <number>
- column-width:	<length> | <percentage>
- empty-cells: show | hide | inherit
- ends-row:	true | false
- number-columns-repeated: <number>
- number-columns-spanned:	<number>
- number-rows-spanned: <number>
- starts-row:	true | false
- table-layout:	auto | fixed | inherit
- table-omit-footer-at-break: true | false
- table-omit-header-at-break: true | false

##Writing-mode-related Properties
- direction:	ltr | rtl | inherit
- glyph-orientation-horizontal:	<angle> | inherit
- glyph-orientation-vertical:	auto | <angle> | inherit
- text-altitude:	use-font-metrics | <length> | <percentage> | inherit
- text-depth:	use-font-metrics | <length> | <percentage> | inherit
- unicode-bidi:	normal | embed | bidi-override | inherit
- writing-mode:	lr-tb | rl-tb | tb-rl | tb-lr | bt-lr | bt-rl | lr-bt | rl-bt | lr-alternating-rl-bt | lr-alternating-rl-tb | lr-inverting-rl-bt | lr-inverting-rl-tb | tb-lr-in-lr-pairs | lr | rl | tb | inherit

##Miscellaneous Properties
- change-bar-class:	<name>
- change-bar-color: <color>
- change-bar-offset: <length>
- change-bar-placement:	start | end | left | right | inside | outside | alternate
- change-bar-style:	<border-style>
- change-bar-width: <border-width>
- content-type:	<string> | auto
- id: <id>
- intrinsic-scale-value: <percentage> | inherit
- page-citation-strategy: [ all | normal | non-blank | inherit
- provisional-label-separation:	<length> | <percentage> | inherit
- provisional-distance-between-starts:	<length> | <percentage> | inherit
- ref-id: <idref> | inherit
- scale-option: width | height | inherit
- score-spaces:	true | false | inherit
- src:	<uri-specification> | inherit
- visibility:	visible | hidden | collapse | inherit
- z-index: auto | <integer> | inherit
- background:	[<background-color> || <background-image> || <background-repeat> || <background-attachment> || <background-position> ]] | inherit
- background-position: [ [<percentage> | <length> ]{1,2} | [ [top | center | bottom] || [left | center | right] ] ] | inherit
- border:	[ <border-width> || <border-style> || [ <color> | transparent ] ] | inherit
- border-bottom|top|left|right:	[ <border-width> || <border-style> || [ <color> | transparent ] ] | inherit
- border-color:	[ <color> | transparent ]{1,4} | inherit
- border-style:	<border-style>{1,4} | inherit
- border-spacing:	<length> <length>? | inherit
- border-width:	<border-width>{1,4} | inherit
- cue:	<cue-before> || <cue-after> | inherit
- font:	[ [ <font-style> || <font-variant> || <font-weight> ]? <font-size> [ / <line-height>]? <font-family> ] | caption | icon | menu | message-box | small-caption | status-bar | inherit
- margin:	<margin-width>{1,4} | inherit
- padding:	<padding-width>{1,4} | inherit
- page-break-after|before:	auto | always | avoid | left | right | inherit
- page-break-inside:	avoid | auto | inherit
- pause:	[<time> | <percentage>]{1,2} | inherit
- position:	static | relative | absolute | fixed | inherit
- size:	<length>{1,2} | auto | landscape | portrait | inherit
- vertical-align:	baseline | middle | sub | super | text-top | text-bottom | <percentage> | <length> | top | bottom | inherit
- white-space:	normal | pre | nowrap | inherit
- xml:lang:	<language-country> | inherit


