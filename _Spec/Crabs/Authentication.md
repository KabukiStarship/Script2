# [SCRIPT Specification](../)

## [Crabs Specification](./)

### Authentication

Authentication in Crabs shall be done using a sequence of Crabs Operations. The authentication process must ensure that only authorized Chinese Rooms can establish connections and access shared resources.

#### Authentication Flow

1. **Initial Handshake**: Both parties exchange authentication tokens during the initial connection handshake.
2. **Token Verification**: Each party verifies the received token using the shared secret or public key infrastructure.
3. **Session Establishment**: Once authentication is successful, a secure session is established.
4. **Token Renewal**: Tokens must be periodically renewed to maintain session security.

#### Token Structure

Authentication tokens must be composed of:
- A 16-bit hash of the shared secret
- A 32-bit timestamp for token expiration
- A 16-bit nonce for replay attack prevention
- A 64-bit session identifier

#### Security Requirements

1. All authentication tokens must be cryptographically secure.
2. Tokens must have a maximum lifetime of 24 hours.
3. Nonces must be unique and non-repeating for each authentication attempt.
4. Failed authentication attempts must be logged and rate-limited.
5. Session keys must be exchanged using a secure key exchange protocol.

#### Example Authentication Sequence

```Crabs
// Example: Authentication sequence using Crabs Operations
OPN auth_request
OPD token_hash: 0x1234567890ABCDEF
OPD timestamp: 0x12345678
OPD nonce: 0x1234
OPD session_id: 0x1234567890ABCDEF

// Server response
OPN auth_response
OPD status: 0x01  // Success
OPD session_key: 0x1234567890ABCDEF
OPD expiration: 0x12345678
```

**[<< Previous Section: Crabs Specification](../) | [Next Section: Portals >>](Portals.md)**

[SCRIPT Specification](../) **>** [SCRIPT Protocol](./)
