# Markdown format
Es el formato usado para los documentos dentro de Github. Su extensión es *.md

## Sintaxis básica
[Mastering Markdown](https://guides.github.com/features/mastering-markdown/)

[Formatting your text with Markdown](https://www.pivotaltracker.com/help/articles/formatting_your_text_with_markdown/)

[Sintaxis de escritura y formato básicos](https://help.github.com/es/github/writing-on-github/basic-writing-and-formatting-syntax)

## Links Relativos
Como hacer referencias a otros documentos o carpetas dentro de el mismo repositorio de GitHub. No siempre está funcionando, hay que terminar de estudiar el tema.

> Instead of an absolute link:
```Markdown
[a link](https://github.com/user/repo/blob/branch/other_file.md)
```
>… you can use a relative link:
```Markdown
[a relative link](other_file.md)
```
> and we’ll make sure it gets linked to: 
```Markdown
user/repo/blob/branch/other_file.md`.
```

> If you were using a workaround like: 
```Markdown
[a workaround link](repo/blob/master/other_file.md)
``` 
> , you’ll have to update your documentation to use the new syntax.

## Syntax highlighting
Sintaxis reconocidas
[] Markdown
[]javascript
[]CPP
[]

> Here’s an example of how you can use syntax highlighting with GitHub Flavored Markdown:
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

## Referencias
[Mastering Markdown](https://guides.github.com/features/mastering-markdown/)

[Formatting your text with Markdown](https://www.pivotaltracker.com/help/articles/formatting_your_text_with_markdown/)

[Sintaxis de escritura y formato básicos](https://help.github.com/es/github/writing-on-github/basic-writing-and-formatting-syntax)

[Relative links in markup files](https://help.github.com/es/github/writing-on-github/basic-writing-and-formatting-syntax)

[About READMEs](https://help.github.com/en/github/creating-cloning-and-archiving-repositories/about-readmes)


