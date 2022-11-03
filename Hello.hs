square :: Integer -> Integer
square a
 | a == 2 = a
 | otherwise = a * a

main :: IO ()
main = do
 print ( square 1 )
 print ( square 2 )
 print ( square 3 )
 print ( square 4 )
