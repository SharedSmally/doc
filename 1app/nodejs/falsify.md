# Falsify 
- [https://github.com/fastify/fastify](falsify framework)
- [Hooks](https://github.com/fastify/fastify/blob/main/docs/Reference/Hooks.md):using fastify.addHook to listen to specific events in the application or request/response lifecycle.
- [Decorators](https://github.com/fastify/fastify/blob/main/docs/Reference/Decorators.md): customization of the core Fastify objects(request,reply.etc) by attaching any type of property to the core objects, e.g. functions, plain objects, or native types.
- [Plugins: Core/Community](https://github.com/fastify/fastify/blob/main/docs/Guides/Ecosystem.md): use register() for Plugins(extened functions): fastify.register(plugin, [options])

## Install: npm i fastify
```
// ESM
import Fastify from 'fastify'
const fastify = Fastify({
  logger: true
})
// CommonJs
const fastify = require('fastify')({
  logger: true
})
//////////////////////////////////////
// Declare a route
fastify.get('/', (request, reply) => {
  reply.send({ hello: 'world' })
})

// Run the server!
fastify.listen({ port: 3000 }, (err, address) => {
  if (err) throw err
  // Server is now listening on ${address}
})
```

## Hook

## Decocrator

## Plugin

