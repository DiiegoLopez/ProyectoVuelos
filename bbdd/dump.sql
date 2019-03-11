--
-- PostgreSQL database dump
--

-- Dumped from database version 10.3
-- Dumped by pg_dump version 10.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: companias; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.companias (
    idcompania integer NOT NULL,
    nombrecompania character varying(100) NOT NULL,
    "nombreLogoCompania" integer NOT NULL,
    "uuidLogoCompania" uuid NOT NULL
);


ALTER TABLE public.companias OWNER TO usuario;

--
-- Name: companias_idCompania_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."companias_idCompania_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."companias_idCompania_seq" OWNER TO usuario;

--
-- Name: companias_idCompania_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."companias_idCompania_seq" OWNED BY public.companias.idcompania;


--
-- Name: companias_nombreLogo_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."companias_nombreLogo_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."companias_nombreLogo_seq" OWNER TO usuario;

--
-- Name: companias_nombreLogo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."companias_nombreLogo_seq" OWNED BY public.companias."nombreLogoCompania";


--
-- Name: destinos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.destinos (
    iddestino integer NOT NULL,
    nombredestino character varying(100) NOT NULL
);


ALTER TABLE public.destinos OWNER TO usuario;

--
-- Name: destinos_idDestino_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."destinos_idDestino_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."destinos_idDestino_seq" OWNER TO usuario;

--
-- Name: destinos_idDestino_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."destinos_idDestino_seq" OWNED BY public.destinos.iddestino;


--
-- Name: estados; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.estados (
    "idEstado" integer NOT NULL,
    "estadoEstado" character varying(255) NOT NULL,
    "horaEstado" time(6) without time zone NOT NULL,
    cancelado boolean DEFAULT false NOT NULL
);


ALTER TABLE public.estados OWNER TO usuario;

--
-- Name: COLUMN estados.cancelado; Type: COMMENT; Schema: public; Owner: usuario
--

COMMENT ON COLUMN public.estados.cancelado IS 'CANCELADO = TRUE - NO CANCELADO = FALSE';


--
-- Name: estados_idEstado_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."estados_idEstado_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."estados_idEstado_seq" OWNER TO usuario;

--
-- Name: estados_idEstado_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."estados_idEstado_seq" OWNED BY public.estados."idEstado";


--
-- Name: estados_vuelos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.estados_vuelos (
    "idVuelo" integer NOT NULL,
    "idEstado" integer NOT NULL
);


ALTER TABLE public.estados_vuelos OWNER TO usuario;

--
-- Name: puertas; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.puertas (
    idpuerta integer NOT NULL,
    letrapuerta character varying(100) NOT NULL,
    numeropuerta integer NOT NULL
);


ALTER TABLE public.puertas OWNER TO usuario;

--
-- Name: puertas_idPuerta_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."puertas_idPuerta_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."puertas_idPuerta_seq" OWNER TO usuario;

--
-- Name: puertas_idPuerta_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."puertas_idPuerta_seq" OWNED BY public.puertas.idpuerta;


--
-- Name: vuelos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.vuelos (
    idvuelo integer NOT NULL,
    idcompania integer NOT NULL,
    iddestino integer NOT NULL,
    idpuerta integer NOT NULL,
    horavuelo time(6) without time zone NOT NULL,
    informacionvuelo character varying(100) NOT NULL
);


ALTER TABLE public.vuelos OWNER TO usuario;

--
-- Name: COLUMN vuelos.informacionvuelo; Type: COMMENT; Schema: public; Owner: usuario
--

COMMENT ON COLUMN public.vuelos.informacionvuelo IS 'SALIDAS/LLEGADAS';


--
-- Name: vuelos_idVuelo_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."vuelos_idVuelo_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."vuelos_idVuelo_seq" OWNER TO usuario;

--
-- Name: vuelos_idVuelo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."vuelos_idVuelo_seq" OWNED BY public.vuelos.idvuelo;


--
-- Name: companias idcompania; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.companias ALTER COLUMN idcompania SET DEFAULT nextval('public."companias_idCompania_seq"'::regclass);


--
-- Name: companias nombreLogoCompania; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.companias ALTER COLUMN "nombreLogoCompania" SET DEFAULT nextval('public."companias_nombreLogo_seq"'::regclass);


--
-- Name: destinos iddestino; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.destinos ALTER COLUMN iddestino SET DEFAULT nextval('public."destinos_idDestino_seq"'::regclass);


--
-- Name: estados idEstado; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados ALTER COLUMN "idEstado" SET DEFAULT nextval('public."estados_idEstado_seq"'::regclass);


--
-- Name: puertas idpuerta; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.puertas ALTER COLUMN idpuerta SET DEFAULT nextval('public."puertas_idPuerta_seq"'::regclass);


--
-- Name: vuelos idvuelo; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.vuelos ALTER COLUMN idvuelo SET DEFAULT nextval('public."vuelos_idVuelo_seq"'::regclass);


--
-- Data for Name: companias; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.companias VALUES (1, 'IBERIA', 1, '40e6215d-b5c6-4896-987c-f30f3678f608');


--
-- Data for Name: destinos; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.destinos VALUES (1, 'DUBAI');


--
-- Data for Name: estados; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.estados VALUES (1, 'EMBARCANDO', '16:00:00', false);


--
-- Data for Name: estados_vuelos; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.estados_vuelos VALUES (1, 1);


--
-- Data for Name: puertas; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.puertas VALUES (1, 'B', 6);


--
-- Data for Name: vuelos; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.vuelos VALUES (1, 1, 1, 1, '13:00:00', 'SALIDA');
INSERT INTO public.vuelos VALUES (2, 1, 1, 1, '15:00:00', 'HOLA');


--
-- Name: companias_idCompania_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."companias_idCompania_seq"', 1, true);


--
-- Name: companias_nombreLogo_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."companias_nombreLogo_seq"', 1, true);


--
-- Name: destinos_idDestino_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."destinos_idDestino_seq"', 1, true);


--
-- Name: estados_idEstado_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."estados_idEstado_seq"', 1, true);


--
-- Name: puertas_idPuerta_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."puertas_idPuerta_seq"', 1, true);


--
-- Name: vuelos_idVuelo_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."vuelos_idVuelo_seq"', 2, true);


--
-- Name: companias companias_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.companias
    ADD CONSTRAINT companias_pkey PRIMARY KEY (idcompania);


--
-- Name: destinos destinos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.destinos
    ADD CONSTRAINT destinos_pkey PRIMARY KEY (iddestino);


--
-- Name: estados estados_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados
    ADD CONSTRAINT estados_pkey PRIMARY KEY ("idEstado");


--
-- Name: puertas puertas_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.puertas
    ADD CONSTRAINT puertas_pkey PRIMARY KEY (idpuerta);


--
-- Name: vuelos vuelos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.vuelos
    ADD CONSTRAINT vuelos_pkey PRIMARY KEY (idvuelo);


--
-- Name: estados_vuelos estados_vuelos_fk1; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados_vuelos
    ADD CONSTRAINT estados_vuelos_fk1 FOREIGN KEY ("idVuelo") REFERENCES public.vuelos(idvuelo) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: estados_vuelos estados_vuelos_fk2; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados_vuelos
    ADD CONSTRAINT estados_vuelos_fk2 FOREIGN KEY ("idEstado") REFERENCES public.estados("idEstado") ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: vuelos vuelos_fk1; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.vuelos
    ADD CONSTRAINT vuelos_fk1 FOREIGN KEY (idcompania) REFERENCES public.companias(idcompania) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: vuelos vuelos_fk2; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.vuelos
    ADD CONSTRAINT vuelos_fk2 FOREIGN KEY (iddestino) REFERENCES public.destinos(iddestino) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: vuelos vuelos_fk3; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.vuelos
    ADD CONSTRAINT vuelos_fk3 FOREIGN KEY (idpuerta) REFERENCES public.puertas(idpuerta) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- PostgreSQL database dump complete
--

