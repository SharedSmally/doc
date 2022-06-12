# Directive
- Structure Direective: NgIf/NgFor
- Attribute Directive: html attribute tag

## Sample
```
import { Directive, ElementRef, Input, OnInit } from '@angular/core';
@Directive({
  selector: '[cardType]'
})
export class CardTypeDirective implements OnInit {
  @Input() cardType: number = 0;
  @Input() increaseClass = 'increase';
  @Input() decreaseClass = 'decrease';
  
  constructor(private el: ElementRef) {}

  ngOnInit() {
    if (this.cardType) {
      if (this.cardType >= 0) {
         this.el.nativeElement.classList.add(this.increaseClass);
          this.el.nativeElement.classList.remove(this.decreaseClass);
      } else if (this.cardType <= 0) {
         this.el.nativeElement.classList.add(this.decreaseClass);
         this.el.nativeElement.classList.remove(this.increaseClass);
      } else {
         this.el.nativeElement.classList.remove(this.increaseClass);
         this.el.nativeElement.classList.remove(this.decreaseClass);
      }
   }
  }
 }
}
```
In template
```
<div [cardType]="stock"></div> .
```

- Modifying a component with a directive with events
```
@Directive({
  selector: '[cardHover]'
})

export class CardHoverDirective implements OnInit {
  card: any;
  constructor(private el: ElementRef) {}
  ngOnInit() {
    this.card = this.el.nativeElement.querySelector('.mdl-card');
    if (this.card.classList.contains('increase')) {
      this.card.style.backgroundColor = 'rgb(63,81,181)';
    } else if (this.card.classList.contains('decrease')) {
      this.card.style.backgroundColor = 'rgb(255,171,64)';
    } else {
      this.card.style.backgroundColor = '';
    }
  }
  @HostListener('mouseover') onMouseOver() {
    this.card.style.boxShadow = '2px 2px 1px #999';
    this.card.style.top = '-2px';
  }
  @HostListener('mouseout') onMouseOut() {
    this.card.style.boxShadow = '';
    this.card.style.top = '';
  }
```
- Structcture Directive
```
import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';
@Directive({
  selector: '[delay]'
})

export class DelayDirective {
  @Input() set delay(ms: number) {
  setTimeout(() => { this.viewContainer.createEmbeddedView(this.templateRef); }, ms);
  }
  constructor(private templateRef: TemplateRef<any>, private viewContainer: ViewContainerRef) {}
```
In template
```
<div class="mdl-cell mdl-cell--3-col" *ngFor="let stock of stocks; index as i">
  <summary [stock]="stock" *delay="i * 100" cardTone></summary>
</div>
```

## Pipe
