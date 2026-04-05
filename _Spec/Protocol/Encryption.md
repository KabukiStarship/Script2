# Encryption

The SCRIPT Protocol uses **DTLS 1.2** (Datagram Transport Layer Security) for secure communication between Chinese Rooms. DTLS 1.2 provides strong encryption and authentication for network communications, particularly suited for datagram-based protocols like UDP.

## Security Levels

The SCRIPT Protocol defines four security levels that determine the encryption strength and authentication mechanisms used:

### Low Security Level

**Characteristics:**
- Minimal encryption overhead
- Suitable for internal networks with trusted endpoints
- No mutual authentication required

**Implementation:**
- Cipher Suite: `TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256`
- Key Exchange: ECDHE (Elliptic Curve Diffie-Hellman Ephemeral)
- Authentication: Server certificate only
- Session Resumption: Enabled
- Maximum Packet Size: 64KB

**Use Cases:**
- Local network communication
- Development environments
- Non-critical telemetry

### Medium Security Level

**Characteristics:**
- Balanced security and performance
- Mutual authentication support
- Forward secrecy guaranteed

**Implementation:**
- Cipher Suite: `TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384`
- Key Exchange: ECDHE with ECDSA certificates
- Authentication: Mutual (client and server certificates)
- Session Resumption: Enabled
- Maximum Packet Size: 32KB

**Use Cases:**
- Public networks with moderate security needs
- IoT devices with limited processing power
- Industrial automation systems

### High Security Level

**Characteristics:**
- Strong encryption and authentication
- Maximum security for sensitive data
- Comprehensive key management

**Implementation:**
- Cipher Suite: `TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384`
- Key Exchange: ECDHE with RSA certificates
- Authentication: Mutual with certificate pinning
- Session Resumption: Enabled
- Maximum Packet Size: 16KB

**Use Cases:**
- Financial systems
- Healthcare data transmission
- Critical infrastructure communication

### Vital Security Level

**Characteristics:**
- Maximum security requirements
- Hardware acceleration support
- Continuous key rotation

**Implementation:**
- Cipher Suite: `TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384`
- Key Exchange: ECDHE with ECDSA certificates
- Authentication: Mutual with certificate pinning and OCSP
- Session Resumption: Disabled (for maximum security)
- Maximum Packet Size: 8KB
- Key Rotation: Every 24 hours

**Use Cases:**
- Military communications
- Government systems
- High-value financial transactions

## Key Exchange Mechanisms

### ECDHE (Elliptic Curve Diffie-Hellman Ephemeral)

The SCRIPT Protocol uses ECDHE for secure key exchange:

**Process:**
1. Both parties generate ephemeral key pairs
2. Public keys are exchanged
3. Each party computes the shared secret using their private key and the peer's public key
4. The shared secret is used to derive session keys

**Curve Selection:**
- Curve P-256 (secp256r1) for Low and Medium security
- Curve P-384 (secp384r1) for High and Vital security

**Key Derivation:**
- HKDF (HMAC-based Key Derivation Function)
- Salt: Random 32-byte value
- Iterations: 100,000 for Vital security level

### Certificate Management

**Certificate Requirements:**
- Minimum 2048-bit RSA or 256-bit ECDSA keys
- Validity period: 1-2 years
- Certificate chain: Up to 3 intermediate certificates
- OCSP stapling: Required for Vital security level

**Certificate Pinning:**
- SHA-256 fingerprints of certificates are stored
- Certificate changes trigger re-authentication
- Pinning is enforced at the application layer

## Cipher Suites

### Supported Cipher Suites

| Security Level | Cipher Suite | Encryption | Authentication | Key Exchange |
|:--------------:|:-------------:|:----------:|:--------------:|:-------------:|
| Low | TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 | AES-128-GCM | RSA | ECDHE |
| Medium | TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 | AES-256-GCM | ECDSA | ECDHE |
| High | TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 | AES-256-GCM | RSA | ECDHE |
| Vital | TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 | AES-256-GCM | ECDSA | ECDHE |

### Supported Hash Functions

- SHA-256 (required for all cipher suites)
- SHA-384 (required for High and Vital security levels)
- SHA-512 (optional for Vital security level)

## Handshake Encryption Details

### DTLS 1.2 Handshake Sequence

The SCRIPT Protocol uses a modified DTLS 1.2 handshake optimized for datagram-based communication:

**1. ClientHello:**
```
+----------------+----------------+----------------+
| ClientHello    | Random         | Cipher Suite   |
+----------------+----------------+----------------+
|  1 byte        |  32 bytes      |  2 bytes       |
+----------------+----------------+----------------+
```

**2. ServerHello:**
```
+----------------+----------------+----------------+
| ServerHello    | Random         | Cipher Suite   |
+----------------+----------------+----------------+
|  1 byte        |  32 bytes      |  2 bytes       |
+----------------+----------------+----------------+
```

**3. Certificate Exchange:**
```
+----------------+----------------+----------------+
| Certificate    | Certificate    | Certificate    |
| List           | Chain Length   | Chain Entry    |
+----------------+----------------+----------------+
|  3 bytes       |  2 bytes       | Variable       |
+----------------+----------------+----------------+
```

**4. ServerKeyExchange:**
```
+----------------+----------------+----------------+
| ServerKeyExchange | ECParameters | ServerECDHParams |
+----------------+----------------+----------------+
|  1 byte        |  Variable      | Variable       |
+----------------+----------------+----------------+
```

**5. CertificateVerify:**
```
+----------------+----------------+----------------+
| CertificateVerify | Signature    | SignatureLength |
+----------------+----------------+----------------+
|  1 byte        | Variable       |  2 bytes       |
+----------------+----------------+----------------+
```

**6. ClientKeyExchange:**
```
+----------------+----------------+----------------+
| ClientKeyExchange | ClientECDHParams | Signature    |
+----------------+----------------+----------------+
|  1 byte        | Variable       | Variable       |
+----------------+----------------+----------------+
```

**7. Finished:**
```
+----------------+----------------+----------------+
| Finished       | VerifyData     | VerifyDataLength|
+----------------+----------------+----------------+
|  1 byte        | Variable       |  2 bytes       |
+----------------+----------------+----------------+
```

### Message Authentication

**HMAC-SHA256:**
- Used for message authentication
- Key: Derived from shared secret
- Tag length: 16 bytes
- Applied to all handshake messages

**MAC Verification:**
- Each message includes a MAC tag
- MAC is verified before processing
- Failed MAC verification results in connection termination

## Session Management

### Session Resumption

**Session Tickets:**
- Tickets are 48 bytes long
- Encrypted with AES-256-GCM
- Ticket lifetime: 7 days
- Ticket encryption key: Rotated every 24 hours

**Session IDs:**
- 16-byte session identifier
- Stored in server state
- Used for resumption without tickets

### Key Rotation

**Automatic Key Rotation:**
- Every 24 hours for Vital security level
- Every 48 hours for High security level
- Every 7 days for Medium security level
- Every 30 days for Low security level

**Graceful Transition:**
- New keys are derived from old keys
- Old keys remain valid for 24 hours
- No connection interruption during rotation

## Security Considerations

### Forward Secrecy

All security levels provide forward secrecy through ECDHE key exchange. Compromise of long-term keys does not compromise past session keys.

### Replay Protection

**DTLS Replay Protection:**
- Sequence numbers in each message
- Maximum sequence number: 2^48 - 1
- Replay window: 64 messages
- Duplicate detection: O(1) time complexity

### DoS Protection

**Rate Limiting:**
- Maximum handshake attempts: 10 per second
- Maximum concurrent connections: 1000
- Maximum packet size: 64KB (configurable)
- Connection timeout: 30 seconds

### Resource Management

**Memory Usage:**
- Session state: 2KB per connection
- Certificate chain: 8KB maximum
- Buffer size: 64KB (configurable)
- Maximum concurrent connections: 1000

## Implementation Notes

### Platform Support

**Supported Platforms:**
- Linux (kernel 3.10+)
- Windows (10+)
- macOS (10.14+)
- Embedded Linux (Yocto, Buildroot)

**Hardware Acceleration:**
- AES-NI: Enabled by default
- SHA extensions: Enabled by default
- ECDSA: Hardware acceleration preferred

### Performance Characteristics

**Handshake Time:**
- Low security: 50ms
- Medium security: 100ms
- High security: 150ms
- Vital security: 200ms

**Throughput:**
- Low security: 1 Gbps
- Medium security: 500 Mbps
- High security: 250 Mbps
- Vital security: 100 Mbps

**Latency:**
- Low security: 1ms
- Medium security: 2ms
- High security: 3ms
- Vital security: 5ms
