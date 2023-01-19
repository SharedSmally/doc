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
```
// This function gets called at build time
export async function getStaticPaths() {
  // Call an external API endpoint to get posts
  const res = await fetch('https://.../posts')
  const posts = await res.json()

  // Get the paths we want to pre-render based on posts
  const paths = posts.map((post) => ({
    params: { id: post.id },
  }))

  // We'll pre-render only these paths at build time.
  // { fallback: false } means other routes should 404.
  return { paths, fallback: false }
}

```
    - page paths depend on external data: Use *getStaticPaths* 
```
export default function Post({ post }) {
  // Render post...
}

export async function getStaticPaths() {
  // ...
}

// This also gets called at build time
export async function getStaticProps({ params }) {
  // params contains the post `id`.
  // If the route is like /posts/1, then params.id is 1
  const res = await fetch(`https://.../posts/${params.id}`)
  const post = await res.json()

  // Pass post data to the page via props
  return { props: { post } }
}
```
- Server-side Rendering: The HTML is generated on each request.
    - export an async function called getServerSideProps. This function will be called by the server on every request.
```
export default function Page({ data }) {
  // Render data...
}

// This gets called on every request
export async function getServerSideProps() {
  // Fetch data from external API
  const res = await fetch(`https://.../data`)
  const data = await res.json()

  // Pass data to the page via props
  return { props: { data } }
}

```
#### Static Generation with data

To use Server-side Rendering for a page, you need 
