------------------
--2017.9
--sule
------------------
{-# LANGUAGE OverloadedStrings #-}
import Network.Wai
import qualified Data.Text as T
import qualified Data.ByteString.Char8 as S
import qualified Data.ByteString.Lazy.Char8 as L
import Network.Wai.Handler.Warp (run)
import Network.HTTP.Types (status200)
import Network.HTTP.Types.Header (hContentType)
import Database.SQLite.Simple
import Database.SQLite.Simple.FromRow
import Control.Applicative
import Data.String


main = run 3002 app

data User = User
  { username :: T.Text
  , password :: T.Text
  } deriving (Show)

data Deck =
  Deck T.Text
       T.Text
       T.Text
       Int

instance FromRow Deck where
  fromRow = Deck <$> field <*> field <*> field <*> field

instance ToRow Deck where
  toRow (Deck n p s l) = toRow (n, p, s, l)


instance FromRow User where
  fromRow = User <$> field <*> field

instance ToRow User where
  toRow (User n p) = toRow (n, p)

failPage f =
  f $responseLBS status200 [(hContentType, S.pack "text/html")] $
  L.pack "<h1> wrong user info </h1>"

htmlPage f s = do
  content <- S.readFile s
  f $responseLBS status200 [(hContentType, S.pack "text/html")] $
    L.fromStrict content

getText=T.pack.S.unpack

submit req f = do
  let query = queryString req
  let owner = head [snd x | x <- query, fst x == S.pack "owner"]
  let deckName = head [snd x | x <- query, fst x == S.pack "deckname"]
  let deck = head [snd x | x <- query, fst x == S.pack "deck"]
  case (owner, deckName, deck) of
    (Just o, Just dn, Just dk) ->
      if S.null o || S.null dn || S.null dk 
        then failPage f
        else do
          conn <- open "datafile.db"
          execute
            conn
            "insert into deck values(?,?,?,?)"
            (Deck (getText o) (getText dn) (getText $ S.cons 'a' dk) 0)
          close conn
          f $
            responseLBS status200 [(hContentType, S.pack "text/html")] $
            L.concat
              [ L.pack "<h1>"
              , L.fromStrict o
              , L.pack " , your deck :"
              , L.fromStrict dn
              , L.pack " has been saved<h1>"
              ]
            

register req f = do
  let query = queryString req
  let mun = head [snd x | x <- query, fst x == S.pack "username"]
  let mpw = head [snd x | x <- query, fst x == S.pack "password"]
  case (mun, mpw) of
    (Just un, Just pw) ->
      if S.null un || S.null pw
        then failPage f
        else do
          conn <- open "datafile.db"
          putStrLn $ S.unpack un ++ "   " ++ S.unpack pw
          execute_
            conn
            "create table if not exists user (username text, password text)"
          execute_
            conn
            "create table if not exists deck (owner text, deckName text, deckCard text, iscurdeck integer)"
          execute
            conn
            "insert into user (username, password) values(?,?)"
            (User (T.pack $ S.unpack un) (T.pack $ S.unpack pw))
          r <- query_ conn "SELECT * from user" :: IO [User]
          mapM_ print r
          putStrLn "register successful!"
          close conn
          f $
            responseLBS status200 [(hContentType, S.pack "text/html")] $
            L.concat
              [ L.pack "<h1>"
              , L.fromStrict un
              , L.pack " register successful<h1>"
              ]
              
addDeck req f = do
  let query = queryString req
  let mun = head [snd x | x <- query, fst x == S.pack "username"]
  let mpw = head [snd x | x <- query, fst x == S.pack "password"]
  case (mun, mpw) of
    (Just un, Just pw) ->
      if S.null un || S.null pw
        then failPage f
        else do
          conn <- open "datafile.db"
          putStrLn $ S.unpack un ++ S.unpack pw ++ "  login"
          users <-
            query_
              conn
              (mconcat
                 [ "select * from user where username="
                 , "'"
                 , fromString (S.unpack un) :: Query
                 , "'"
                 ]) :: IO [User]
          print users
          if null users
            then failPage f
            else if (username (head users) == getText un) &&
                    (password (head users) == getText pw)
                   then f $
                        responseLBS
                          status200
                          [(hContentType, S.pack "text/html")] $
                        deckPage un
                   else failPage f
      where getText = T.pack . S.unpack       



deckPage n =
  L.concat $
  map
    L.pack
    [ "<form action=\"/submit\" method=\"get\"><div><label for=\"deckname\">deckname</label><input name=\"deckname\"></div><div><label for=\"deck\">deck</label><input name=\"deck\"></div><button>submit</button></div><input name=\"owner\" type=\"hidden\" value=\""
    , S.unpack n
    , "\"></form>"
    ]



app :: Application
app req f = do
  let r = pathInfo req
  if null r
    then htmlPage f "register.html"
    else do
      let act
            | head r == T.pack "register" = register req f
            | head r == T.pack "login" = htmlPage f "login.html"
            | head r == T.pack "adddeck" = addDeck req f
            | head r == T.pack "submit" = submit req f
            | otherwise = failPage f
      act
