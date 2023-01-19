# [next](https://nextjs.org/)
- [API doc]()
- [Tutorial]()

## setup
Install react,react-dom,typescript,next
```
npx create-next-app@latest --typescript
```
Next.js is built around the concept of pages. A page is a React Component exported from a .js, .jsx, .ts, or .tsx file in the pages/ directory
- pages/ - Associated with a route based on their file name. For example pages/about.js is mapped to /about
- public/ - Stores static assets such as images, fonts, etc. Inside Files can be referenced starting from the base URL (/).

### Pre-rendering
- Static Generation (Recommended): The HTML is generated at build time and will be reused on each request.
    - No depends on external data
    - page content depends on external data: Use *getStaticProps*.
    - page paths depend on external data: Use *getStaticPaths* 
- Server-side Rendering: The HTML is generated on each request.
    - export an async function called getServerSideProps. This function will be called by the server on every request.

#### Static Generation with data

To use Server-side Rendering for a page, you need 
