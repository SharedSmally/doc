#[XSL 1.1](https://www.w3.org/TR/2006/REC-xsl11-20061205/)
    
## 7.31 Shorthand Properties
 - background: 
  [<background-color> || <background-image> || <background-repeat> || <background-attachment> || <background-position> ]] | inherit
 - background-position
	[ [<percentage> | <length> ]{1,2} | [ [top | center | bottom] || [left | center | right] ] ] | inherit
 - border, border-bottom, border-top, border-left, border-right
	[ <border-width> || <border-style> || [ <color> | transparent ] ] | inherit
 - border-width, border-color, border-style, border-spacing  
 - cue
  <cue-before> || <cue-after> | inherit 
 - font
	[ [ <font-style> || <font-variant> || <font-weight> ]? <font-size> [ / <line-height>]? <font-family> ] | caption | icon | menu | message-box | small-caption | status-bar | inherit
 - margin
  <margin-width>{1,4} | inherit
 - padding
  <padding-width>{1,4} | inherit
 - page-break-after; page-break-before; page-break-inside
  	auto | always | avoid | left | right | inherit
 - pause
 	  [<time> | <percentage>]{1,2} | inherit
 - position
   static | relative | absolute | fixed | inherit
 - size
   <length>{1,2} | auto | landscape | portrait | inherit
 - vertical-align
   baseline | middle | sub | super | text-top | text-bottom | <percentage> | <length> | top | bottom | inherit
 - white-space
   normal | pre | nowrap | inherit
 - xml:lang
