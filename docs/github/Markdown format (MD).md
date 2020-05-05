# Markdown format
Es el formato usado para los documentos dentro de Github. Su extensión es *.md

## Referencias y links
[Mastering Markdown](https://guides.github.com/features/mastering-markdown/)

[Formatting your text with Markdown](https://www.pivotaltracker.com/help/articles/formatting_your_text_with_markdown/)

[Sintaxis de escritura y formato básicos](https://help.github.com/es/github/writing-on-github/basic-writing-and-formatting-syntax)

Syntax highlighting
Here’s an example of how you can use syntax highlighting with GitHub Flavored Markdown:
[Creating and highlighting code blocks](https://help.github.com/en/github/writing-on-github/creating-and-highlighting-code-blocks)

Examples:

```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```

```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```



