-- obiekt regulacji
function Inercja1(enter, last) -- 1/(5s+1)
    local out = (Tp / (5 + Tp)) * enter + (5 / (5 + Tp)) * last
    return out
  end

  function Inercja2(enter, last) -- 2/3s+1
    local out = ((Tp / (3 + Tp)) * enter + (3 / (3 + Tp)) * last/2)*2
    return out
  end

  function Obiekt(enter, last1, last2)
    local mid = Inercja1(enter, last1)
    local out = Inercja2(mid, last2)
    return out, mid
  end

-- parametry symulacji
local expected = 1
local real = 0
local tmax = 20
Tp = 0.1

-- zmienne obiektu
local mid = 0

-- pętla regulacji
File = io.open("result_ob.csv", "w")
for times = (0 + Tp), tmax, Tp
do
  real, mid = Obiekt(expected, mid, real)
  local f_times = string.gsub(string.format("%.1f", times), "%.", ",")
  local f_real = string.gsub(string.format("%.8f", real), "%.", ",")
  File:write(f_times,"\t",f_real, "\n")
  print(times , string.format("%.6f",real))
end
File:close()
print("ok")